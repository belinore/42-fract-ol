# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/22 18:28:30 by belinore          #+#    #+#              #
#    Updated: 2025/03/31 16:53:44 by belinore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fract-ol

HDR = fract_ol.h

SRC = $(SRC_DIR)/main.c $(SRC_DIR)/init.c $(SRC_DIR)/fractals.c \
		$(SRC_DIR)/colors.c $(SRC_DIR)/events.c $(SRC_DIR)/events_2.c \
		$(SRC_DIR)/errors.c $(SRC_DIR)/render.c $(SRC_DIR)/utils.c
SRC_DIR = src

LIBFTPRINTF	= $(LIBFTPRINTF_DIR)/libftprintf.a
LIBFTPRINTF_DIR	= ft_printf

OBJS := $(SRC:%.c=%.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -O2

# Define OS-specific flags
ifeq ($(shell uname), Darwin)  # macOS
INCLUDES = -Imlx/minilibx_macos
    LFLAGS = -L ./mlx/minilibx_macos \
              -l mlx -framework OpenGL -framework Appkit \
			  -L$(LIBFTPRINTF_DIR) -lftprintf
else  # Assume Linux
INCLUDES = -Imlx/minilibx-linux
    LFLAGS = -L./mlx/minilibx-linux \
              -l mlx_Linux -l X11 -l Xext -l Xrender -l GL -lm \
			  -L$(LIBFTPRINTF_DIR) -lftprintf
endif

all: $(LIBFTPRINTF) $(NAME)

$(NAME): $(OBJS) $(LIBFTPRINTF) 
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFTPRINTF):
	@ $(MAKE) -C $(LIBFTPRINTF_DIR)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFTPRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

debug:
	@echo "Sources: $(SRC)"
	@echo "Objects: $(OBJS)"
	@echo "CC Command: $(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(LFLAGS)"
