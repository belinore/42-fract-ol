/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:27:35 by belinore          #+#    #+#             */
/*   Updated: 2025/08/29 15:45:12 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

// mandelbrot formula:
// z = z^2 + c
// where z starts at 0, 0
// c is the pixel converted to the complex plane
// 
// squaring a complex number:
// (x + yi)(x + yi)
// x^2 + 2xyi + yi^2
// x^2 + 2xyi + y(-1)^2
// x^2 + 2xyi - y^2 
// real part is x^2 - y^2
// imaginary is 2*x*y
void	mandelbrot(t_point p, t_vars *vars, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	double		x2;
	double		y2;
	int			i;

	i = 0;
	z.xr = 0.0;
	z.yi = 0.0;
	c.xr = scale(p.x, fractal->min.x, fractal->max.x, WIDTH) + fractal->x_shift;
	c.yi = scale(p.y, fractal->min.y, fractal->max.y, HEIGHT) + fractal->y_shift;
	while (i < vars->fractal.iterations)
	{
		x2 = z.xr * z.xr;
		y2 = z.yi * z.yi;
		z.yi = (2 * z.xr * z.yi) + c.yi;
		z.xr = x2 - y2 + c.xr;
		if (x2 + y2 > vars->fractal.max_value)
		{
			pthread_mutex_lock(&vars->mutex);
			put_pixel(&vars->img, p.x, p.y, get_color(i, vars));
			pthread_mutex_unlock(&vars->mutex);
			return ;
		}
		i++;
	}
	put_pixel(&vars->img, p.x, p.y, BLACK);
}

// julia formula:
// z = z^2 + c
// c is a constant complex number
// z is the pixel converted to the complex plane
void	julia(t_point p, t_vars *vars, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	double		x2;
	double		y2;
	int			i;

	i = 0;
	c = fractal->c;
	z.xr = scale(p.x, fractal->min.x, fractal->max.x, WIDTH) + fractal->x_shift;
	z.yi = scale(p.y, fractal->min.y, fractal->max.y, HEIGHT) + fractal->y_shift;
	while (i < vars->fractal.iterations)
	{
		x2 = z.xr * z.xr;
		y2 = z.yi * z.yi;
		z.yi = (2 * z.xr * z.yi) + c.yi;
		z.xr = x2 - y2 + c.xr;
		if (x2 + y2 > vars->fractal.max_value)
		{
			put_pixel(&vars->img, p.x, p.y, get_color(i, vars));
			return ;
		}
		i++;
	}
	put_pixel(&vars->img, p.x, p.y, BLACK);
}

// burning ship formula:
// same as mandelbrot but uses the absolute value of z^2
// z = |z^2| + c
void	burning_ship(t_point p, t_vars *vars, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	double		x2;
	double		y2;
	int			i;

	i = 0;
	z.xr = 0.0;
	z.yi = 0.0;
	c.xr = scale(p.x, fractal->min.x, fractal->max.x, WIDTH) + fractal->x_shift;
	c.yi = scale(p.y, fractal->min.y, fractal->max.y, HEIGHT) + fractal->y_shift;
	while (i < vars->fractal.iterations)
	{
		x2 = z.xr * z.xr;
		y2 = z.yi * z.yi;
		z.yi = fabs(2 * z.xr * z.yi) + c.yi;
		z.xr = x2 - y2 + c.xr;
		if (x2 + y2 > vars->fractal.max_value)
		{
			put_pixel(&vars->img, p.x, p.y, get_color(i, vars));
			return ;
		}
		i++;
	}
	put_pixel(&vars->img, p.x, p.y, BLACK);
}

// burning ship julia sets formula:
// same as julia but uses the absolute value of z^2
void	julia_ship(t_point p, t_vars *vars, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	double		x2;
	double		y2;
	int			i;

	i = 0;
	c = vars->fractal.c;
	z.xr = scale(p.x, fractal->min.x, fractal->max.x, WIDTH) + fractal->x_shift;
	z.yi = scale(p.y, fractal->min.y, fractal->max.y, HEIGHT) + fractal->y_shift;
	while (i < vars->fractal.iterations)
	{
		x2 = z.xr * z.xr;
		y2 = z.yi * z.yi;
		z.yi = fabs(2 * z.xr * z.yi) + c.yi;
		z.xr = x2 - y2 + c.xr;
		if (x2 + y2 > vars->fractal.max_value)
		{
			put_pixel(&vars->img, p.x, p.y, get_color(i, vars));
			return ;
		}
		i++;
	}
	put_pixel(&vars->img, p.x, p.y, BLACK);
}
