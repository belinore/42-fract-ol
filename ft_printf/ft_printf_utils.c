/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:45:21 by belinore          #+#    #+#             */
/*   Updated: 2025/03/31 21:59:19 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(char c, int *print_len)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	*print_len += 1;
	return (0);
}

int	print_string(char *str, int *print_len)
{
	if (str == NULL)
	{
		if (ft_putstr("(null)") == -1)
			return (-1);
		*print_len += 6;
	}
	else
	{
		if (ft_putstr(str) == -1)
			return (-1);
		*print_len += ft_strlen(str);
	}
	return (0);
}

int	print_number(int nbr, char c, int *print_len)
{
	if (c == 'd' || c == 'i')
	{
		*print_len += ft_count_digits(nbr);
		if (ft_putnbr(nbr) == -1)
			return (-1);
	}
	else if (c == 'u')
	{
		*print_len += ft_count_digits((unsigned int)nbr);
		if (ft_putnbr_unsigned((unsigned int)nbr) == -1)
			return (-1);
	}
	return (0);
}

int	print_float(double nbr, int *print_len)
{
	ft_putnbr_float(nbr, 6);
	*print_len += ft_count_digits((int)nbr) + 7;
	return (0);
}

int	print_hexadec(size_t nbr, char format, int *print_len)
{
	int	x;

	x = 0;
	if (format == 'p')
	{
		if (nbr == 0)
		{
			*print_len += 3;
			return (ft_putstr("0x0"));
		}
		if (ft_putstr("0x") == -1)
			return (-1);
		*print_len += 2;
		x = ft_putnbr_base(nbr, "0123456789abcdef", print_len);
	}
	else if (format == 'x')
		x = ft_putnbr_base((unsigned int)nbr, "0123456789abcdef", print_len);
	else if (format == 'X')
		x = ft_putnbr_base((unsigned int)nbr, "0123456789ABCDEF", print_len);
	if (x == -1)
		return (-1);
	return (0);
}
