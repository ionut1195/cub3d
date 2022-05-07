# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/12 16:49:20 by aricholm          #+#    #+#              #
#    Updated: 2021/07/07 18:39:28 by aricholm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Werror -Wall -Wextra
NAME = libft.a
HEAD = libft.h
OBJS = \
ft_strchr.o ft_strlcat.o ft_strlcpy.o ft_strlen.o ft_strncmp.o \
ft_bzero.o ft_memcpy.o ft_memccpy.o ft_memmove.o ft_memset.o \
ft_memcmp.o ft_calloc.o ft_memchr.o ft_strdup.o \
ft_strrchr.o ft_strnstr.o ft_itoa.o ft_atoi.o \
ft_isalpha.o ft_isalnum.o ft_isascii.o ft_isdigit.o ft_isprint.o \
ft_strjoin.o ft_strtrim.o ft_substr.o ft_toupper.o ft_tolower.o \
ft_strmapi.o ft_split.o \
ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o
SRC = \
ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memset.c \
ft_memcmp.c ft_calloc.c ft_memchr.c ft_strdup.c \
ft_strrchr.c ft_strnstr.c ft_itoa.c ft_atoi.c \
ft_isalpha.c ft_isalnum.c ft_isascii.c ft_isdigit.c ft_isprint.c \
ft_strjoin.c ft_strtrim.c ft_substr.c ft_toupper.c ft_tolower.c \
ft_strmapi.c ft_split.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
ft_lstiter.c ft_lstmap.c
BONUS = \
ft_lstnew.o ft_lstadd_front.o ft_lstsize.o ft_lstlast.o \
ft_lstadd_back.o ft_lstdelone.o ft_lstclear.o \
ft_lstiter.o ft_lstmap.o

all : $(NAME)

$(NAME): $(OBJS)
	ar rc $@ $^
	rm -f $(OBJS) $(BONUS)

%.o: %.c $(HEAD)
	$(CC) -c $(CFLAGS)  -o $@  $<

clean:
	echo "Remove .o  ..."
	rm -f $(OBJS) $(BONUS)

fclean: clean
	echo "Remove lib ..."
	rm -f $(NAME)

re: fclean all

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRC)
	gcc -nostartfiles -shared -o libft.so $(OBJS) $(BONUS)

bonus: $(OBJS) $(BONUS)
	ar rc $(NAME) $(OBJS) $(BONUS)

.PHONY: all clean fclean re bonus