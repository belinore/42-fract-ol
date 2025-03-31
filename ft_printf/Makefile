# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 14:58:40 by belinore          #+#    #+#              #
#    Updated: 2025/03/21 19:08:02 by belinore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

HDR = ft_printf.h

SRC = ft_count_digits.c ft_printf.c ft_printf_utils.c ft_putstr.c ft_putnbr.c \
	ft_putnbr_base.c ft_putnbr_unsigned.c ft_strlen.c ft_putnbr_float.c

OBJS := $(SRC:%.c=%.o)

CC = cc -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) -I. -o $@ -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: all
	$(CC) main.c $(NAME) && ./a.out

.PHONY: all clean fclean re
