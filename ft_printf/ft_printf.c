/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:30:48 by belinore          #+#    #+#             */
/*   Updated: 2025/03/21 18:33:38 by belinore         ###   ########.fr       */
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
