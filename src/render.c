/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:27:23 by belinore          #+#    #+#             */
/*   Updated: 2025/09/04 18:46:18 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

double  now_in_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0);
}

void	render_fractal(t_vars *vars)
{
	double start = now_in_ms();//to remove
	if (vars->img.img_ptr)
		mlx_destroy_image(vars->mlx, vars->img.img_ptr);
	vars->img.img_ptr = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (vars->img.img_ptr == NULL)
	{
		mlx_destroy_window(vars->mlx, vars->window);
		error_malloc_failure();
	}
	vars->img.pixel_ptr = mlx_get_data_addr(vars->img.img_ptr, &vars->img.bpp,
			&vars->img.line_length, &vars->img.endian);
	if (vars->fractal.code == 'm')
		vars->fract_calc = mandelbrot;
	else if (vars->fractal.code == 'j')
		vars->fract_calc = julia;
	else if (vars->fractal.code == 'b')
		vars->fract_calc = burning_ship;
	else if (vars->fractal.code == 's')
		vars->fract_calc = julia_ship;
	add_pixels_to_image(vars);
	mlx_put_image_to_window(vars->mlx, vars->window, vars->img.img_ptr, 0, 0);
	double end = now_in_ms(); //to remove
	printf("Render time: %.2f ms\n", end - start);
}

void	render_section(int pixel_y, int end_y, t_vars *vars)
{
	int	pixel_x;

	while (pixel_y < end_y)
	{
		pixel_x = 0;
		while (pixel_x < WIDTH)
		{
			vars->fract_calc(pixel_x, pixel_y, vars, &vars->fractal);
			pixel_x++;
		}
		pixel_y++;
	}
}

void	*thread_render_section(void *arg)
{
	t_thread *thread;
	int		start_row;
	int		end_row;

	thread = (t_thread *)arg;
	while (1)
	{
		pthread_mutex_lock(&thread->vars->threads.mutex);
		while (thread->vars->threads.frame_id == thread->last_frame && !thread->vars->threads.stop)
            pthread_cond_wait(&thread->vars->threads.cond, &thread->vars->threads.mutex);
		if (thread->vars->threads.stop)	
			break ;
		start_row = thread->vars->threads.next_row;
		if (start_row >= HEIGHT)
		{
			thread->last_frame = thread->vars->threads.frame_id;
			thread->vars->threads.work_done++;
			if (thread->vars->threads.work_done == thread->vars->threads.nb_threads)
            	pthread_cond_signal(&thread->vars->threads.cond);
			pthread_mutex_unlock(&thread->vars->threads.mutex);	
			continue ;
		}
		end_row = start_row + ROWS_PER_TASK;
		if (end_row > HEIGHT)
			end_row = HEIGHT;
		thread->vars->threads.next_row += ROWS_PER_TASK;
        pthread_mutex_unlock(&thread->vars->threads.mutex);		
		render_section(start_row, end_row, thread->vars);
	}
	pthread_mutex_unlock(&thread->vars->threads.mutex);
	return (NULL);
}

void	add_pixels_to_image(t_vars *vars)
{	
	if (vars->threads.multithreading)
	{
		pthread_mutex_lock(&vars->threads.mutex);
    	vars->threads.work_done = 0;
		vars->threads.next_row = 0;
		vars->threads.frame_id++;
		//fprintf(stderr, "[main] broadcasting, work_done reset to 0\n");
		pthread_cond_broadcast(&vars->threads.cond);
		while (vars->threads.work_done < vars->threads.nb_threads)
        	pthread_cond_wait(&vars->threads.cond, &vars->threads.mutex);
		//fprintf(stderr, "[main] all workers done (work_done=%d)\n", vars->threads.work_done);
		pthread_mutex_unlock(&vars->threads.mutex);
		return ;
	}
	else
		render_section(0, HEIGHT, vars);
}

// Linear interpolation to convert pixels from a 0 to WIDTH (x axis)
// and 0 to HEIGHT (y axis) grid, to a -2 to 2 (x) and -2 to to 2 (y)
// grid at the relevant zoom for fractals
double	scale(double unscaled_num, double new_min, double new_max,
		double old_max)
{
	double	old_min;

	old_min = 0;
	return (((new_max - new_min) * (unscaled_num - old_min)) / (old_max
			- old_min) + new_min);
}

/* double	scale(int pixel, double min, double max, int size)
{
	return ((max - min) * pixel / size + min);
} */

// writes a pixel to an image. note: pixel_ptr points to the first pixel in
// the image buffer so we compute offset to locate the relevant pixel
void	put_pixel(t_img *img, int x, int y, int color)
{
	int	offset;

	offset = (y * img->line_length) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixel_ptr + offset) = color;
}
