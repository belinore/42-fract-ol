/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:27:32 by belinore          #+#    #+#             */
/*   Updated: 2025/03/24 15:49:44 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

static double	atod_get_fraction(const char *str)
{
	double	fraction;
	double	div;

	fraction = 0;
	div = 10;
	while (*str >= '0' && *str <= '9')
	{
		fraction += (*str - '0') / div;
		div *= 10;
		str++;
	}
	return (fraction);
}

double	ft_atod(const char *str)
{
	int		sign;
	double	num;
	double	fraction;

	sign = 1;
	num = 0;
	fraction = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while ((*str >= '0' && *str <= '9'))
	{
		num *= 10;
		num += (*str - '0');
		str++;
	}
	if (*str++ == '.')
		fraction = atod_get_fraction(str);
	return ((sign * num) + (sign * fraction));
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
		{
			if ((unsigned char)s1[i] < (unsigned char)s2[i])
				return (-1);
			return (1);
		}
		i++;
	}
	return (0);
}
