# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/07 10:21:55 by aricholm          #+#    #+#              #
#    Updated: 2022/05/07 13:35:54 by aricholm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PATH_LIBFT = libft
NAME = cub3D
LIBFT = $(PATH_LIBFT)/libft.a
OBJ = obj
SRC = src
SRCS = cub3d.c parser.c get_next_line.c

OBJS     = $(SRCS:%.c=$(OBJ)/%.o)

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
LFLAGS = -lm

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LFLAGS) -o $(NAME)

$(LIBFT):	
	@$(MAKE) -C $(PATH_LIBFT)

$(OBJS): $(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -fr $(OBJ)
	@$(MAKE) clean -C $(PATH_LIBFT)

fclean: clean
	rm -f $(NAME)
	@$(MAKE) fclean -C $(PATH_LIBFT)


re: fclean all

.PHONY: all clean fclean re