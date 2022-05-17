/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closed_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:14:35 by aricholm          #+#    #+#             */
/*   Updated: 2022/05/17 13:50:33 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*		THIS IS FOR TESTING ONLY!!   */
/*************************************/
// void printtmp(char **tmp, t_map *map)
// {
// 	for (int i = 0; i < map->height; i++)
// 	{
// 		for (int j = 0; j < map->width; j++)
// 		{
// 			printf("%c", tmp[j][i]);
// 		}
// 		printf("\n");
// 	}
// }
/*************************************/

static void	destroy_tmp(char **tmp, t_map *map)
{
	int	i;

	i = 0;
	if (!tmp)
		return ;
	while (i < map->width)
		free(tmp[i++]);
	free(tmp);
}

static char	**build_tmp(t_cub3d *cub3d)
{
	char	**out;
	int		i;

	out = malloc(sizeof(char *) * cub3d->map->width);
	if (!out)
		exit_error(cub3d, "Error while allocating memory");
	i = 0;
	while (i < cub3d->map->width)
	{
		out[i] = malloc(sizeof(char) * cub3d->map->height);
		if (!out[i])
		{
			while (i)
				free(out[--i]);
			free(out);
			exit_error(cub3d, "Error while allocating memory");
		}
		i++;
	}
	return (out);
}

static void	fill_tmp(char **tmp, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->height)
		{
			tmp[i][j] = map->map[i][j];
			if (tmp[i][j] == 'N' || tmp[i][j] == 'W'
				|| tmp[i][j] == 'S' || tmp[i][j] == 'E')
			{
				map->startd = tmp[i][j];
				tmp[i][j] = 'X';
				map->startx = i;
				map->starty = j;
			}
			j++;
		}
		i++;
	}
//printtmp(tmp, map);
}

static	int	infect(char **tmp, int i, int j, t_cub3d *c)
{
	if (i == 0 || j == 0 || i == c->map->width || j == c->map->height
		|| tmp[i - 1][j] == ' ' || tmp[i + 1][j] == ' '
		|| tmp[i][j - 1] == ' ' || tmp[i][j + 1] == ' ')
	{
		destroy_tmp(tmp, c->map);
		exit_error(c, "Map is not surrounded by walls");
	}
	if (tmp[i - 1][j] != '0' && tmp[i + 1][j] != '0'
		&& tmp[i][j - 1] != '0' && tmp[i][j + 1] != '0')
		return (0);
	if (tmp[i - 1][j] == '0')
		tmp[i - 1][j] = 'X';
	if (tmp[i + 1][j] == '0')
		tmp[i + 1][j] = 'X';
	if (tmp[i][j + 1] == '0')
		tmp[i][j + 1] = 'X';
	if (tmp[i][j - 1] == '0')
		tmp[i][j - 1] = 'X';
	return (1);
}

void	validate_closedwalls(t_cub3d *cub3d)
{
	char	**tmp;
	int		i;
	int		j;
	int		x;

	tmp = build_tmp(cub3d);
	fill_tmp(tmp, cub3d->map);
	x = 1;
	while (x)
	{
		x = 0;
		i = 0;
		while (i < cub3d->map->width)
		{
			j = 0;
			while (j < cub3d->map->height)
			{
				if (tmp[i][j] == 'X')
					x += infect(tmp, i, j, cub3d);
				j++;
			}
			i++;
		}
	}
	destroy_tmp(tmp, cub3d->map);
}
