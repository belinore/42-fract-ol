/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 20:00:02 by belinore          #+#    #+#             */
/*   Updated: 2025/03/21 18:33:59 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(size_t nbr, char *base, int *print_len)
{
	unsigned int	base_len;
	char			num;

	base_len = ft_strlen(base);
	if (nbr >= base_len)
		ft_putnbr_base(nbr / base_len, base, print_len);
	num = base[nbr % base_len];
	if (write(1, &num, 1) == -1)
		return (-1);
	*print_len += 1;
	return (0);
}
