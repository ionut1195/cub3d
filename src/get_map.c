/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:00:55 by aricholm          #+#    #+#             */
/*   Updated: 2022/05/17 10:17:36 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*		map is indexed from the upper left corner
**		
**		(0,0) > (1,0) > ... > (n,0)
**		 V
**		(0,1) > (1,1) > ... > (n,1)
**		 V
**		...
**		 V
**		(0,m) > (1,m) > ... > (n,m)
*/

/*		THIS IS FOR TESTING ONLY!!*/
void printmap(t_map *map)
{
	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
		{
			printf("%c", map->map[j][i]);
		}
		printf("\n");
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
}

static void	allocate_map(t_map *mapstruct)
{
	int		i;
	char	**map;

	i = 0;
	mapstruct->map = malloc(sizeof(char *) * mapstruct->width);
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
		while (j < map->width)
			map->map[j++][i] = '1';
		i++;
	}
}



t_bool	get_map(t_cub3d *cub3d, const char **lines)
{
	get_map_size(cub3d->map, lines);
	allocate_map(cub3d->map);
	if (!cub3d->map)
		return (FALSE);
	fill_map(cub3d->map, lines);
	printmap(cub3d->map);
	return (TRUE);
}
