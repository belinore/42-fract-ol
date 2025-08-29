/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:27:23 by belinore          #+#    #+#             */
/*   Updated: 2025/08/29 17:49:27 by belinore         ###   ########.fr       */
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
	double start = now_in_ms();
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
		add_pixels_to_image(vars, mandelbrot);
	else if (vars->fractal.code == 'j')
		add_pixels_to_image(vars, julia);
	else if (vars->fractal.code == 'b')
		add_pixels_to_image(vars, burning_ship);
	else if (vars->fractal.code == 's')
		add_pixels_to_image(vars, julia_ship);
	mlx_put_image_to_window(vars->mlx, vars->window, vars->img.img_ptr, 0, 0);
	double end = now_in_ms();
	printf("Render time: %.2f ms\n", end - start);
}

void	*thread_render_section(void *arg)
{
	t_thread *thread;
	t_point	pixel;

	thread = (t_thread *)arg;
	pixel.y = thread->start_y;
	while (pixel.y < thread->end_y)
	{
		pixel.x = 0;
		while (pixel.x < WIDTH)
		{
			//mandelbrot(pixel, thread->vars, &thread->vars->fractal);
			thread->vars->fract_calc(pixel, thread->vars, &thread->vars->fractal);
			pixel.x++;
		}
		pixel.y++;
	}
	return (NULL);
}

void	divide_pixels_per_thread(t_vars *vars, int nb_threads, void (*fractal)
							(t_point,t_vars *, t_fractal *))
{
	int	section_size;
	int i;

	section_size = HEIGHT / nb_threads;
	vars->fract_calc = fractal;
	pthread_mutex_init(&vars->mutex, NULL);
	i = 0;
	while (i < nb_threads)
	{
		vars->threads[i].start_y = i * section_size;
		vars->threads[i].end_y = (i == nb_threads - 1) ? HEIGHT : (i + 1) * section_size; //???
		vars->threads[i].id = i;
		vars->threads[i].vars = vars;
		pthread_create(&vars->threads[i].thread, NULL, thread_render_section, &vars->threads[i]);
		i++;
	}
	i = 0;
	while (i < nb_threads)
	{
		pthread_join(vars->threads[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(&vars->mutex);
}

void	add_pixels_to_image(t_vars *vars, void (*fractal)(t_point p, t_vars *,
							t_fractal *))
{
	t_point pixel;
	int		nb_threads;
		
	nb_threads = sysconf(_SC_NPROCESSORS_ONLN) - 1;
	if (nb_threads < 1 || vars->multithreading == 0)
		nb_threads = 1;
	else if (nb_threads > MAX_CORES)
		nb_threads = MAX_CORES;
	if (nb_threads > 1)
	{
		divide_pixels_per_thread(vars, nb_threads, fractal);
		return ;
	}
	pixel.y = 0;
	while (pixel.y < HEIGHT)
	{
		pixel.x = 0;
		while (pixel.x < WIDTH)
		{
			fractal(pixel, vars, &vars->fractal);
			pixel.x++;
		}
		pixel.y++;
	}
}

// void	add_pixels_to_image(t_vars *vars, void (*fractal)(t_point p, t_vars *,
// 							t_fractal *))
// {
// 	int			x;
// 	int			y;

// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			fractal(x, y, vars, &vars->fractal);
// 			x++;
// 		}
// 		y++;
// 	}
// }

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
