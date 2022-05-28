# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/07 10:21:55 by aricholm          #+#    #+#              #
#    Updated: 2022/05/28 19:04:40 by aricholm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PATH_LIBFT = libft
NAME = cub3D
LIBFT = $(PATH_LIBFT)/libft.a
OBJ = obj
SRC = src
SRCS =	cub3d.c\
		parser.c\
		add_texture.c\
		get_map.c\
		validate.c\
		cleanup.c\
		draw_line.c\
		raycast.c\
		move.c

OBJS     = $(SRCS:%.c=$(OBJ)/%.o)

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
LFLAGS = -lm

OS:= $(shell uname -s)
ifeq ($(OS),Darwin)
	MLXFLAGS = mlx/libmlx.a -Lmlx -lmlx -framework OpenGL -framework AppKit
	INCDIR = mac
endif
ifeq ($(OS),Linux)
	MLXFLAGS = mlx_linux/libmlx.a -L/usr/X11/lib -I/opt/X11/include -lXext -lX11 -lm -lz -g
	INCDIR = linux
endif


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LFLAGS) -o $(NAME) $(MLXFLAGS)

$(LIBFT):	
	@$(MAKE) -C $(PATH_LIBFT)

$(OBJS): $(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -I $(INCDIR) -o $@ $<

clean:
	rm -fr $(OBJ)
	@$(MAKE) clean -C $(PATH_LIBFT)

fclean: clean
	rm -f $(NAME)
	@$(MAKE) fclean -C $(PATH_LIBFT)


re: fclean all

.PHONY: all clean fclean re