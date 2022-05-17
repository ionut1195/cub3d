/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:00:55 by aricholm          #+#    #+#             */
/*   Updated: 2022/05/11 15:35:05 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void printmap(t_map *map)
{
	for (int i = 0; i < map->width; i++)
	{
		for (int j = 0; i < map->height; i++)
		{
			printf("%d", map->map[j][i]);
		}
		write(1, "\n", 1);
	}
}

static void	get_map_size(t_map *map, const char **lines)
{
	int		y;
	int		maxx;
	int		len;

	y = 0;
	maxx = 0;
	while (lines[y])
	{
		len = ft_strlen(lines[y]);
		if (len > maxx)
			maxx = len;
		y++;
	}
	map->width = maxx;
	map->height = y;
printf("the map is %dx%d\n", maxx, y);
}

static void	allocate_map(t_map *mapstruct)
{
	int		i;
	char	**map;

	i = 0;
	mapstruct->map = malloc(sizeof(char) * mapstruct->width);
	if (!mapstruct->map)
		return ;
	map = mapstruct->map;
	while (i < mapstruct->width)
	{
		map[i] = malloc(sizeof(char) * mapstruct->height);
		if (!map[i])
		{
			while (i != 0)
				free(map[--i]);
			free(map);
			map = NULL;
			return ;
		}
		ft_bzero(map[i], mapstruct->height);
		i++;
	}
}

static void	fill_map(t_map *map, const char **lines)
{
	int	i;
	int	j;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] == ' ')
				map->map[j][i] = '1';
			else
				map->map[j][i] = lines[i][j];
			j++;
		}
		printf("%s\n", map->map[j]);
		i++;
	}
}



t_bool	get_map(t_cub3d *cub3d, const char **lines)
{
	get_map_size(cub3d->map, lines);
	allocate_map(cub3d->map);
	if (!cub3d->map)
		return (FALSE);
	printmap(cub3d->map);
	fill_map(cub3d->map, lines);
	printmap(cub3d->map);
	return (TRUE);
}
