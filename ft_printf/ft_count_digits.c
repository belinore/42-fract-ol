/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:45:45 by belinore          #+#    #+#             */
/*   Updated: 2025/03/21 18:33:48 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	count_digits(ssize_t num)
{
	int	count;

	count = 0;
	if (num == -2147483648)
		return (11);
	else if (num < 0)
	{
		count++;
		num = -num;
	}
	else if (num == 0)
		return (1);
	while (num > 0)
	{
		num = num / 10;
		count++;
	}
	return (count);
}
