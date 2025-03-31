/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:30:48 by belinore          #+#    #+#             */
/*   Updated: 2025/03/31 21:54:15 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	args_ptr;
	int		print_len;

	if (str == NULL)
		return (-1);
	va_start(args_ptr, str);
	print_len = 0;
	if (printer(args_ptr, str, &print_len) == -1)
		return (-1);
	va_end(args_ptr);
	return (print_len);
}

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
		else
			x = print_variable(&args_ptr, str[i + 1], print_len);
		if (x == -1)
			return (-1);
		if (str[i] == '%')
			i++;
		i++;
	}
	return (0);
}

int	print_variable(va_list *args_ptr, const char format, int *print_len)
{
	int	x;

	x = 0;
	if (format == 'c')
		x = print_char(va_arg(*args_ptr, unsigned int), print_len);
	else if (format == 's')
		x = print_string(va_arg(*args_ptr, char *), print_len);
	else if (format == 'p' || format == 'x' || format == 'X')
		x = print_hexadec(va_arg(*args_ptr, size_t), format, print_len);
	else if (format == 'd' || format == 'i' || format == 'u')
		x = print_number(va_arg(*args_ptr, int), format, print_len);
	else if (format == 'f')
		x = print_float(va_arg(*args_ptr, double), print_len);
	else
		return (-1);
	return (x);
}
