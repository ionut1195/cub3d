/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 09:56:12 by aricholm          #+#    #+#             */
/*   Updated: 2022/06/03 11:43:56 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static char	**get_lines(int fd)
{
	char	*text;
	char	*tmp;
	char	buffer[BUFFER_SIZE + 1];
	char	**out;

	text = ft_strdup("");
	ft_bzero(buffer, BUFFER_SIZE + 1);
	while (read(fd, buffer, BUFFER_SIZE) > 0)
	{
		tmp = ft_strjoin(text, buffer);
		ft_bzero(buffer, BUFFER_SIZE + 1);
		free(text);
		text = tmp;
	}
	out = ft_split(text, '\n');
	free(text);
	return (out);
}

static void	get_texture(t_cub3d *cub3d, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' && line[i])
		i++;
	if (line[i] == 0)
		return ;
	if (!add_texture(&cub3d->textures, &line[i]))
		cub3d->textures.flag = 0b1000000;
	return ;
}

/* flag:
		 000001: north texture
		 000010: south texture
		 000100: east texture
		 001000: west texture
		 010000: floor color
		 100000: ceiling color
		1000000: error
*/

static void	parse(t_cub3d *cub3d, char **lines)
{
	int	i;

	i = 0;
	while (cub3d->textures.flag != 0b111111 && lines[i]
		&& cub3d->textures.flag != 0b1000000)
		get_texture(cub3d, lines[i++]);
	if (cub3d->textures.flag == 0b1000000 || !lines[i])
	{
		printf("Error\n%s: Invalid texture info\n", lines[i - 1]);
		destroy_everything(cub3d);
		exit (1);
	}
	while (!lines[i][0])
		i++;
	if (get_map(cub3d, (const char **)&lines[i]) == FALSE)
		exit_error(cub3d, "Error while allocating the map");
	destroy_lines(lines);
	cub3d->lines = NULL;
}

void	parser(t_cub3d *cub3d, const char *file)
{
	int		fd;
	char	**lines;

	fd = check_file(file);
	lines = get_lines(fd);
	cub3d->lines = lines;
	if (!lines)
	{
		printf("Error\n: Error while reading the .cub file\n");
		exit (1);
	}
	parse(cub3d, lines);
	return ;
}
