/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:27:23 by belinore          #+#    #+#             */
/*   Updated: 2025/03/24 13:54:12 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	render_fractal(t_vars *vars)
{
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
}

void	add_pixels_to_image(t_vars *vars, void (*fractal)(int, int, t_vars *,
							t_fractal *))
{
	int			x;
	int			y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			fractal(x, y, vars, &vars->fractal);
			x++;
		}
		y++;
	}
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
