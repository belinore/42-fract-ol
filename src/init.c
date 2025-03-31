/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:26:56 by belinore          #+#    #+#             */
/*   Updated: 2025/03/27 14:40:17 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	initialize_colors(t_vars *vars)
{
	vars->colors.palette_size = MAX_PALETTE_SIZE;
	vars->colors.option = BLENDED;
	set_base_colors(&vars->colors, COLORS_1);
	generate_blended_palette(&vars->colors, &vars->fractal);
}

void	initialize_fractal_params(t_fractal *fractal)
{
	double	aspect_ratio;

	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	fractal->x_shift = 0.0;
	fractal->y_shift = 0.0;
	fractal->zoom = 1.0;
	fractal->min.y = 2.0;
	fractal->max.y = -2.0;
	fractal->min.x = -2.0 * aspect_ratio;
	fractal->max.x = 2.0 * aspect_ratio;
	fractal->max_value = 4;
	fractal->iterations = ITERATIONS;
	if (fractal->code == 'b')
	{
		fractal->min.y = -2.0;
		fractal->max.y = 0.5;
		fractal->min.x = -2.5;
		fractal->max.x = 2.0;
	}
	else if (fractal->code == 'j' || fractal->code == 's')
	{
		fractal->max_value = 10;
		fractal->c.xr = -0.8;
		fractal->c.yi = 0.156;
	}
}

void	initialize_events(t_vars *vars)
{
	mlx_hook(vars->window, ON_KEYDOWN, 1L << 0, key_handler, vars);
	mlx_hook(vars->window, ON_MOUSEDOWN, 1L << 2, mouse_handler, vars);
	mlx_hook(vars->window, ON_MOUSEMOVE, 1L << 6, move_handler, vars);
	mlx_hook(vars->window, ON_DESTROY, 1L << 2, close_window, vars);
}

void	initialize_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (vars->mlx == NULL)
		error_malloc_failure();
	vars->window = mlx_new_window(vars->mlx, WIDTH, HEIGHT, vars->fractal.name);
	if (vars->window == NULL)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		error_malloc_failure();
	}
	vars->img.img_ptr = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (vars->img.img_ptr == NULL)
	{
		mlx_destroy_window(vars->mlx, vars->window);
		mlx_destroy_display(vars->mlx);
	}
	vars->img.pixel_ptr = mlx_get_data_addr(vars->img.img_ptr, &vars->img.bpp,
			&vars->img.line_length, &vars->img.endian);
}

void	print_instructions(void)
{
	ft_printf("***** INSTRUCTIONS *****\n");
	ft_printf("Zoom in/out: mouse wheel down/up\n");
	ft_printf("Move up/down/left/right: W/A/S/D\n");
	ft_printf("Switch to Julia: Left click (c is set based on mouse pos)\n");
	ft_printf("Switch back from Julia: Right mouse button\n");
	ft_printf("Evolve Julia: Arrow keys or ENTER to toggle mouse\n");
	ft_printf("Change iterations: SPACE to double, BACKSPACE to halve; ");
	ft_printf("'+' or '-' for small changes; \n");
	ft_printf("Reset fractal: R\n");
	ft_printf("Change colors: Number keys 1 - 8\n");
	ft_printf("************************\n");
}
