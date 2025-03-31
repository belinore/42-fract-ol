/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:32:48 by belinore          #+#    #+#             */
/*   Updated: 2025/03/21 19:32:07 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		count_digits(ssize_t num);
int		ft_printf(const char *text, ...);
int		ft_putnbr(int n);
int		ft_putnbr_base(size_t nbr, char *base, int *print_len);
int     ft_putnbr_float(double num, int decimal_places);
int		ft_putnbr_unsigned(unsigned int n);
int		ft_putstr(char *s);
int		ft_strlen(const char *s);
int		printer(va_list args_ptr, const char *str, int *print_len);

#endif
