/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:54:52 by belinore          #+#    #+#             */
/*   Updated: 2025/03/31 21:39:05 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_float(double num, int decimal_places)
{
	int	integer;
	int	decimal;

	integer = (int)num;
	if (ft_putnbr(integer) == -1)
		return (-1);
	if (decimal_places > 0)
	{
		if (write(1, ".", 1) == -1)
			return (-1);
		num = num - integer;
		if (num < 0)
			num = -num;
		while (decimal_places > 0)
		{
			num *= 10;
			decimal = (int)num;
			if (ft_putnbr(decimal) == -1)
				return (-1);
			num = num - decimal;
			decimal_places--;
		}
	}
	return (0);
}
