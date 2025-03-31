/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:45:21 by belinore          #+#    #+#             */
/*   Updated: 2025/03/21 19:32:56 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_char(char c, int *print_len);
static int	print_string(char *str, int *print_len);
static int	print_number(int nbr, char c, int *print_len);
static int	print_hexadec(size_t nbr, char format, int *print_len);
static int	print_float(double nbr, int *print_len);


int	printer(va_list args_ptr, const char *str, int *print_len)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (str[i])
	{
		if (str[i] != '%' || (str[i] == '%' && str[i + 1] == '%'))
			x = print_char(str[i], print_len);
		else if (str[i + 1] == 'c')
			x = print_char(va_arg(args_ptr, unsigned int), print_len);
		else if (str[i + 1] == 's')
			x = print_string(va_arg(args_ptr, char *), print_len);
		else if (str[i + 1] == 'p' || str[i + 1] == 'x' || str[i + 1] == 'X')
			x = print_hexadec(va_arg(args_ptr, size_t), str[i + 1], print_len);
		else if (str[i + 1] == 'd' || str[i + 1] == 'i' || str[i + 1] == 'u')
			x = print_number(va_arg(args_ptr, int), str[i + 1], print_len);
		else if (str[i + 1] == 'f')
			x = print_float(va_arg(args_ptr, double), print_len);
		else
			return (-1);
		if (x == -1)
			return (-1);
		if (str[i] == '%')
			i++;
		i++;
	}
	return (0);
}

static int	print_char(char c, int *print_len)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	*print_len += 1;
	return (0);
}

static int	print_string(char *str, int *print_len)
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

static int	print_number(int nbr, char c, int *print_len)
{
	if (c == 'd' || c == 'i')
	{
		*print_len += count_digits(nbr);
		if (ft_putnbr(nbr) == -1)
			return (-1);
	}
	else if (c == 'u')
	{
		*print_len += count_digits((unsigned int)nbr);
		if (ft_putnbr_unsigned((unsigned int)nbr) == -1)
			return (-1);
	}
	return (0);
}

static int print_float(double nbr, int *print_len)
{
	ft_putnbr_float(nbr, 6);
	*print_len += count_digits((int)nbr) + 7;
	return (0);
}	

static int	print_hexadec(size_t nbr, char format, int *print_len)
{
	int	x;

	x = 0;
	if (format == 'p')
	{
		if (nbr == 0)
		{
			*print_len += 5;
			return (ft_putstr("(nil)"));
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
