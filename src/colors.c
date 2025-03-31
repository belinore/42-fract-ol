/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 20:53:00 by belinore          #+#    #+#             */
/*   Updated: 2025/03/24 13:53:30 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

static void	set_base_colors_ext(t_colors *color_params, int keycode);

int	get_color(int i, t_vars *vars)
{
	int	color;

	if (vars->colors.option == BLENDED)
		color = vars->colors.palette[i % vars->colors.palette_size];
	else if (vars->colors.option == STRIPED)
		color = vars->colors.base_colors[i % vars->colors.base_colors_count];
	else
		color = scale(i, BLACK, WHITE, vars->fractal.iterations);
	return (color);
}

void	set_base_colors(t_colors *color_params, int keycode)
{
	color_params->base_colors_count = 5;
	if (keycode == COLORS_1 || keycode == COLORS_5)
	{
		color_params->base_colors[0] = 0x272757;
		color_params->base_colors[1] = 0x800080;
		color_params->base_colors[2] = RED;
		color_params->base_colors[3] = 0xFFFF00;
		color_params->base_colors[4] = 0xab20fd;
	}
	else if (keycode == COLORS_2 || keycode == COLORS_6)
	{
		color_params->base_colors[0] = 0xb284be;
		color_params->base_colors[1] = 0x3df09c;
		color_params->base_colors[2] = 0xf0e43d;
		color_params->base_colors[3] = 0xf09c3d;
		color_params->base_colors[4] = 0xf03d3d;
	}
	else
		set_base_colors_ext(color_params, keycode);
}

static void	set_base_colors_ext(t_colors *color_params, int keycode)
{
	color_params->base_colors_count = 6;
	if (keycode == COLORS_3 || keycode == COLORS_7)
	{
		color_params->base_colors[0] = 0x0b00a5;
		color_params->base_colors[1] = 0x1908ff;
		color_params->base_colors[2] = 0xFF13F0;
		color_params->base_colors[3] = 0x08eeff;
		color_params->base_colors[4] = 0xf0ff13;
		color_params->base_colors[5] = 0xff9813;
	}
	else
	{
		color_params->base_colors[0] = 0x383838;
		color_params->base_colors[1] = 0x5c5c5c;
		color_params->base_colors[2] = 0x909090;
		color_params->base_colors[3] = 0xaeaeae;
		color_params->base_colors[4] = WHITE;
		color_params->base_colors[5] = BLACK;
	}
}

void	generate_blended_palette(t_colors *params, t_fractal *fractal)
{
	int	i;
	int	j;
	int	k;
	int	section_size;
	int	transitions;

	if (fractal->iterations < MAX_PALETTE_SIZE)
		params->palette_size = fractal->iterations;
	transitions = params->base_colors_count - 1;
	section_size = params->palette_size / transitions;
	i = 0;
	k = 0;
	while (i < transitions)
	{
		j = 0;
		while (j < section_size)
		{
			params->palette[k++] = interpolate_color(params->base_colors[i],
					params->base_colors[i + 1], (double)j++ / section_size);
		}
		i++;
	}
	while (k < params->palette_size)
		params->palette[k++] = params->base_colors[params->base_colors_count
			- 1];
}

int	interpolate_color(int color1, int color2, double t)
{
	int	r;
	int	g;
	int	b;

	r = ((1 - t) * ((color1 >> 16) & 0xFF)) + (t * ((color2 >> 16) & 0xFF));
	g = ((1 - t) * ((color1 >> 8) & 0xFF)) + (t * ((color2 >> 8) & 0xFF));
	b = ((1 - t) * (color1 & 0xFF)) + (t * (color2 & 0xFF));
	return ((r << 16) | (g << 8) | b);
}
