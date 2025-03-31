/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:27:27 by belinore          #+#    #+#             */
/*   Updated: 2025/03/24 13:53:41 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

static void	adjust_iterations(int keycode, t_vars *vars)
{
	if (keycode == PLUS_ITERS)
		vars->fractal.iterations += 5;
	else if (keycode == MINUS_ITERS)
		vars->fractal.iterations -= 5;
	else if (keycode == DOUBLE_ITERS)
		vars->fractal.iterations *= 2;
	else if (keycode == HALVE_ITERS)
		vars->fractal.iterations /= 2;
	ft_printf("[Iters = %i] ", vars->fractal.iterations);
	generate_blended_palette(&vars->colors, &vars->fractal);
}

static void	evolve_julia(int keycode, t_vars *vars)
{
	if (keycode == UP_ARROW)
		vars->fractal.c.yi += 0.01;
	else if (keycode == DOWN_ARROW)
		vars->fractal.c.yi -= 0.01;
	else if (keycode == RIGHT_ARROW)
		vars->fractal.c.xr += 0.01;
	else if (keycode == LEFT_ARROW)
		vars->fractal.c.xr -= 0.01;
	ft_printf("[c = %fr, %fi] ", vars->fractal.c.xr, vars->fractal.c.yi);
}

static void	move(t_vars *vars, int keycode)
{
	if (keycode == A_MOVE_LEFT)
		vars->fractal.x_shift -= (0.5 * vars->fractal.zoom);
	else if (keycode == D_MOVE_RIGHT)
		vars->fractal.x_shift += (0.5 * vars->fractal.zoom);
	else if (keycode == W_MOVE_UP && vars->fractal.code != 'b')
		vars->fractal.y_shift += (0.5 * vars->fractal.zoom);
	else if (keycode == S_MOVE_DOWN && vars->fractal.code != 'b')
		vars->fractal.y_shift -= (0.5 * vars->fractal.zoom);
	else if (keycode == W_MOVE_UP)
		vars->fractal.y_shift -= (0.5 * vars->fractal.zoom);
	else if (keycode == S_MOVE_DOWN)
		vars->fractal.y_shift += (0.5 * vars->fractal.zoom);
}

static void	change_colors(int keycode, t_vars *vars)
{
	set_base_colors(&vars->colors, keycode);
	if (keycode == COLORS_1 || keycode == COLORS_2 || keycode == COLORS_3
		|| keycode == COLORS_4)
		vars->colors.option = BLENDED;
	else if (keycode == COLORS_5 || keycode == COLORS_6 || keycode == COLORS_7
		|| keycode == COLORS_8)
		vars->colors.option = STRIPED;
	else
		vars->colors.option = 0;
	if (vars->colors.option == BLENDED)
		generate_blended_palette(&vars->colors, &vars->fractal);
}

int	key_handler(int keycode, t_vars *vars)
{
	if (keycode == ESC)
		close_window(vars);
	else if (keycode == PLUS_ITERS || keycode == MINUS_ITERS
		|| keycode == DOUBLE_ITERS || keycode == HALVE_ITERS)
		adjust_iterations(keycode, vars);
	else if (keycode == UP_ARROW || keycode == DOWN_ARROW
		|| keycode == RIGHT_ARROW || keycode == LEFT_ARROW)
		evolve_julia(keycode, vars);
	else if (keycode == ENTER_MOUSE_EVOLVE)
		vars->mouse_evolve = !vars->mouse_evolve;
	else if (keycode == W_MOVE_UP || keycode == S_MOVE_DOWN
		|| keycode == A_MOVE_LEFT || keycode == D_MOVE_RIGHT)
		move(vars, keycode);
	else if (keycode == COLORS_1 || keycode == COLORS_2 || keycode == COLORS_3
		|| keycode == COLORS_4 || keycode == COLORS_5 || keycode == COLORS_6
		|| keycode == COLORS_7 || keycode == COLORS_8 || keycode == COLORS_0)
		change_colors(keycode, vars);
	else if (keycode == R_RESET)
		initialize_fractal_params(&vars->fractal);
	render_fractal(vars);
	return (0);
}
