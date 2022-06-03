# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 17:55:36 by aricholm          #+#    #+#              #
#    Updated: 2022/06/03 11:57:56 by aricholm         ###   ########.fr        #
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
		validate2.c\
		draw_line.c\
		raycast.c\
		move.c\
		rotate.c\
		keypress.c\
		init_textures.c\
		minimap.c

OBJS     = $(SRCS:%.c=$(OBJ)/%.o)

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
LFLAGS = -lm

OS:= $(shell uname -s)
ifeq ($(OS),Darwin)
	MLX = @$(MAKE) -C mlx_mac
	MLXFLAGS = -I mlx_mac  mlx_mac/libmlx.a -Lmlx_mac -lmlx -framework OpenGL -framework AppKit
	INCDIR = -I mac -I mlx_mac
	CLEANUP = cleanup_mac.c
endif
ifeq ($(OS),Linux)
	MLX = @$(MAKE) -C mlx_linux
	MLXFLAGS = -I mlx_linux mlx_linux/libmlx.a -L/usr/X11/lib -I/opt/X11/include -lXext -lX11 -lm -lz -g
	INCDIR = -I linux -I mlx_linux
	CLEANUP = cleanup_linux.c
endif

CLEANOBJ     = $(CLEANUP:%.c=$(OBJ)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(CLEANOBJ) $(LIBFT)
	$(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(CLEANOBJ) $(LIBFT) $(LFLAGS) -o $(NAME) $(MLXFLAGS)

$(LIBFT):	
	@$(MAKE) -s -C $(PATH_LIBFT)

$(OBJS): $(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(INCDIR) -o $@ $<

$(CLEANOBJ): $(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $(INCDIR) -o $@ $<

clean:
	rm -fr $(OBJ)
	@$(MAKE) clean -s -C $(PATH_LIBFT)

fclean: clean
	rm -f $(NAME)
	@$(MAKE) fclean -C $(PATH_LIBFT)


re: fclean all

.PHONY: all clean fclean re