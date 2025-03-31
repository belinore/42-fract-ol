/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:36:04 by belinore          #+#    #+#             */
/*   Updated: 2025/03/24 15:46:49 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	error_malloc_failure(void)
{
	perror("Malloc error\n");
	exit(1);
}

void	error_input(void)
{
	ft_printf("Accepted arguments:\n\"./fract-ol mandelbrot\"\n");
	ft_printf("\"./fract-ol julia <float1> <float2>\"\n");
	ft_printf("\"./fract-ol burningship\"\n");
	exit(1);
}

int	is_valid_input(char *str)
{
	int	i;
	int	dec_pt;

	i = 0;
	dec_pt = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9') && str[i] != '.')
			error_input();
		if (str[i] == '.')
			dec_pt++;
		i++;
	}
	if (dec_pt > 1 || i > 20 || str[i] != '\0')
		error_input();
	return (1);
}
