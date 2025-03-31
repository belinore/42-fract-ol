/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:27:15 by belinore          #+#    #+#             */
/*   Updated: 2025/03/24 15:42:12 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int	main(int argc, char **argv)
{
	static t_vars	vars;

	if ((argc == 2 && ft_strncmp(argv[1], "mandelbrot", 6) == 0)
		|| ((argc == 2 || argc == 4) && ft_strncmp(argv[1], "julia", 5) == 0)
		|| ((argc == 2 || argc == 4)
			&& ft_strncmp(argv[1], "burningship", 7) == 0))
	{
		vars.fractal.name = argv[1];
		vars.fractal.code = argv[1][0];
		initialize_fractal_params(&vars.fractal);
		if (argc == 4 && is_valid_input(argv[2]) && is_valid_input(argv[3]))
		{
			vars.fractal.c.xr = ft_atod(argv[2]);
			vars.fractal.c.yi = ft_atod(argv[3]);
		}
		initialize_mlx(&vars);
		initialize_events(&vars);
		initialize_colors(&vars);
		render_fractal(&vars);
		print_instructions();
		mlx_loop(vars.mlx);
	}
	else
		error_input();
	return (0);
}
