/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:45:35 by belinore          #+#    #+#             */
/*   Updated: 2025/03/21 18:34:02 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_unsigned(unsigned int n)
{
	unsigned long	num;
	char			c;

	num = n;
	if (num >= 10)
	{
		ft_putnbr_unsigned(num / 10);
	}
	c = num % 10 + '0';
	if (write(1, &c, 1) == -1)
		return (-1);
	return (0);
}
