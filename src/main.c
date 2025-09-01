/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:27:15 by belinore          #+#    #+#             */
/*   Updated: 2025/09/01 18:54:46 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	initialize_threads(t_vars *vars)
{
	int	i;
	//int section_size;
	
	pthread_mutex_init(&vars->threads.mutex, NULL);
	pthread_cond_init(&vars->threads.cond, NULL);
	vars->threads.work_done = 0;
	vars->threads.stop = 0;
	vars->threads.frame_id = -1;
	//section_size = HEIGHT / vars->threads.nb_threads;
	i = 0;
	while (i < vars->threads.nb_threads)
	{
		//vars->threads.thread[i].start_y = i * section_size;
		//vars->threads.thread[i].end_y = (i == vars->threads.nb_threads - 1) ? HEIGHT : (i + 1) * section_size; //???
		vars->threads.thread[i].id = i;
		vars->threads.thread[i].vars = vars;
		vars->threads.thread[i].last_frame = -1;
		pthread_create(&vars->threads.thread[i].thread, NULL, thread_render_section, &vars->threads.thread[i]);
		i++;
	}
	//printf("initialized %i threads\n", i);
}

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
//		initialize_threads(&vars);
		render_fractal(&vars);
		print_instructions();
		mlx_loop(vars.mlx);
	}
	else
		error_input();
	return (0);
}
