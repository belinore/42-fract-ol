/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:27:11 by belinore          #+#    #+#             */
/*   Updated: 2025/03/27 14:39:14 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	zoom(double zoom_factor, t_vars *vars)
{
	t_point	zoom_center;
	t_point	before;
	t_point	after;
	double	range_x;
	double	range_y;

	before.x = scale(vars->mouse.x, vars->fractal.min.x, vars->fractal.max.x,
			WIDTH);
	before.y = scale(vars->mouse.y, vars->fractal.min.y, vars->fractal.max.y,
			HEIGHT);
	vars->fractal.zoom *= zoom_factor;
	zoom_center.x = (vars->fractal.min.x + vars->fractal.max.x) / 2.0;
	zoom_center.y = (vars->fractal.min.y + vars->fractal.max.y) / 2.0;
	range_x = (vars->fractal.max.x - vars->fractal.min.x) * zoom_factor;
	range_y = (vars->fractal.max.y - vars->fractal.min.y) * zoom_factor;
	vars->fractal.min.x = zoom_center.x - range_x / 2.0;
	vars->fractal.min.y = zoom_center.y - range_y / 2.0;
	vars->fractal.max.x = zoom_center.x + range_x / 2.0;
	vars->fractal.max.y = zoom_center.y + range_y / 2.0;
	after.x = scale(vars->mouse.x, vars->fractal.min.x, vars->fractal.max.x,
			WIDTH);
	after.y = scale(vars->mouse.y, vars->fractal.min.y, vars->fractal.max.y,
			HEIGHT);
	vars->fractal.x_shift += (before.x - after.x);
	vars->fractal.y_shift += (before.y - after.y);
}

void	switch_to_julia(t_vars *vars, t_fractal *prev)
{
	if (prev->code == 'm')
		vars->fractal.code = 'j';
	else if (prev->code == 'b')
		vars->fractal.code = 's';
	else
		return ;
	initialize_fractal_params(&vars->fractal);
	vars->fractal.c.xr = scale(vars->mouse.x, prev->min.x, prev->max.x, WIDTH)
		+ prev->x_shift;
	vars->fractal.c.yi = scale(vars->mouse.y, prev->min.y, prev->max.y, HEIGHT)
		+ prev->y_shift;
	render_fractal(vars);
	ft_printf("[c = %fr, %fi] ", vars->fractal.c.xr, vars->fractal.c.yi);
}

int	mouse_handler(int mousecode, int x, int y, t_vars *vars)
{
	static t_fractal	params_backup;

	if (mousecode == LEFT_CLICK && (vars->fractal.code == 'm'
			|| vars->fractal.code == 'b') && x >= 0 && x < WIDTH && y >= 0
		&& y < HEIGHT)
	{
		params_backup = vars->fractal;
		switch_to_julia(vars, &params_backup);
	}
	else if (mousecode == RIGHT_CLICK && params_backup.code != 0)
		vars->fractal = params_backup;
	else if (mousecode == SCROLL_DOWN)
		zoom(0.9, vars);
	else if (mousecode == SCROLL_UP)
		zoom(1.1, vars);
	else
		return (0);
	render_fractal(vars);
	return (0);
}

int	move_handler(int x, int y, t_vars *vars)
{
	vars->mouse.x = x;
	vars->mouse.y = y;
	if (vars->mouse_evolve && (vars->fractal.code == 'j'
			|| vars->fractal.code == 's'))
	{
		vars->fractal.c.xr = scale(x, vars->fractal.min.x, vars->fractal.max.x,
				WIDTH) + vars->fractal.x_shift;
		vars->fractal.c.yi = scale(y, vars->fractal.min.y, vars->fractal.max.y,
				HEIGHT) + vars->fractal.y_shift;
		render_fractal(vars);
	}
	return (0);
}

int	close_window(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img.img_ptr);
	mlx_destroy_window(vars->mlx, vars->window);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}
