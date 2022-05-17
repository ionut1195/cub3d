/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:38:23 by aricholm          #+#    #+#             */
/*   Updated: 2022/05/09 13:51:43 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**get_lines(int fd)
{
	char	*text;
	char	*tmp;
	char	*buffer[BUFFER_SIZE + 1];
	char	**out;

	text = ft_strdup("");
	while (read(fd, buffer, BUFFER_SIZE) > 0)
	{
		tmp = ft_strjoin(text, buffer);
		free(text);
		text = tmp;
	}
	out = ft_split(text, '\n');
	free(text);
	close(fd);
	return (out);
}
