/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:32:48 by belinore          #+#    #+#             */
/*   Updated: 2025/03/31 21:20:40 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int	count_digits(ssize_t num);
int	ft_putnbr(int n);
int	ft_putnbr_base(size_t nbr, char *base, int *print_len);
int	ft_putnbr_float(double num, int decimal_places);
int	ft_putnbr_unsigned(unsigned int n);
int	ft_putstr(char *s);
int	ft_strlen(const char *s);

//ft_printf.c
int	ft_printf(const char *text, ...);
int	printer(va_list args_ptr, const char *str, int *print_len);
int	print_variable(va_list *args_ptr, const char format, int *print_len);

//ft_printf_utils.c
int	print_char(char c, int *print_len);
int	print_string(char *str, int *print_len);
int	print_number(int nbr, char c, int *print_len);
int	print_hexadec(size_t nbr, char format, int *print_len);
int	print_float(double nbr, int *print_len);

#endif
