/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 12:51:51 by aricholm          #+#    #+#             */
/*   Updated: 2022/05/07 15:32:57 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*get_line(char **str)
{
	int		i;
	char	*out;
	char	*tmp;

	i = 0;
	if (!*str)
		return (NULL);
	while ((*str)[i] != '\n' && (*str)[i])
		i++;
	out = ft_substr(*str, 0, i);
	tmp = ft_substr(*str, i + 1, ft_strlen(*str) - i - 1);
	if (!out || !tmp)
	{
		free(out);
		free(tmp);
		free(*str);
		printf("Error\n%s\n", strerror(errno));
		exit(errno);
	}
	free(*str);
	// if (tmp[0] == 0)
	// 	*str = NULL;
	// else
	*str = tmp;
	return (out);
}

static int	add_buffer(char **str, int fd)
{
	int		chars_read;
	char	buffer[BUFFER_SIZE + 1];
	char	*out;

	ft_bzero(buffer, BUFFER_SIZE + 1);
	chars_read = read(fd, buffer, BUFFER_SIZE);
	if (chars_read < 0)
		return (-1);
	if (chars_read == 0)
		return (TRUE);
	out = ft_calloc(ft_strlen(*str) + chars_read + 1, 1);
	if (!out)
		return (-1);
	ft_strlcpy(out, *str, ft_strlen(*str) + 1);
	ft_strlcat(out, buffer, chars_read + ft_strlen(*str) + 1);
	free(*str);
	*str = out;
	return (FALSE);
}

static t_bool	has_eol(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (FALSE);
	while (str[i])
	{
		if (str[i] == '\n')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

char	*get_next_line(int fd)
{
	static char	*string = NULL;
	int			eof;
	char		*out;

	eof = 0;
	while (!has_eol(string) && !eof)
		eof = add_buffer(&string, fd);
	if (eof < 0)
	{
		free(string);
		printf("Error\n%s\n", strerror(errno));
		exit(errno);
	}
	out = get_line(&string);
	return (out);
}
