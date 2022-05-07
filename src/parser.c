/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 09:56:12 by aricholm          #+#    #+#             */
/*   Updated: 2022/05/07 14:26:37 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_file(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\n%s: %s\n", file, strerror(errno));
		exit (errno);
	}
	if (ft_strncmp(&file[ft_strlen(file) - 4], ".cub", 4))
	{
		close(fd);
		printf("Error\n%s: File is not a .cub file\n", file);
		exit (1);
	}
	if (read(fd, NULL, 0) == -1)
	{
		close(fd);
		printf("Error\n%s: %s\n", file, strerror(errno));
		exit (errno);
	}
	return (fd);
}

static void	parse(t_cub3d *cub3d, int fd)
{
	char *txt;
	(void) cub3d;
	for (size_t i = 0; i < 25; i++)
	{
			txt = get_next_line(fd);
		printf("%s\n", txt);
		free(txt);
	}
	
}

void	parser(t_cub3d *cub3d, const char *file)
{
	int		fd;

	fd = check_file(file);
	parse(cub3d, fd);
	close(fd);
	return ;
}
