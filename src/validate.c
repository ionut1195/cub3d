/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 10:22:30 by aricholm          #+#    #+#             */
/*   Updated: 2022/06/01 12:37:38 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*POSSIBLE LEGAL MAP OBJECTS CAN BE ADDED HERE*/
static t_bool	invalid_object(char c)
{
	const char		legal[] = "NWES 01";
	static t_bool	flag = FALSE;
	int				i;

	i = 0;
	while (legal[i])
	{
		if (c == legal[i++])
		{
			if (i < 4)
			{
				if (flag)
					return (TRUE);
				else
					flag = TRUE;
			}
			return (FALSE);
		}
	}
	return (TRUE);
}

static void	validate_map(t_cub3d *cub3d)
{
	int		i;
	int		j;
	t_map	*map;

	map = &cub3d->map;
	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->height)
		{
			if (invalid_object(map->map[i][j]))
				exit_error(cub3d, "Invalid map object");
			if (map->map[i][j] == '0' &&
				(i == 0 || j == 0 || i == map->width || j == map->height
				|| map->map[i - 1][j] == ' ' || map->map[i + 1][j] == ' '
				|| map->map[i][j - 1] == ' ' || map->map[i][j + 1] == ' '))
				exit_error(cub3d, "Map is not surrounded by walls");
			j++;
		}
		i++;
	}
}

static void	get_start(t_cub3d *c, int x, int y)
{
	c->player.pos.x = x + 0.5;
	c->player.pos.y = y + 0.5;
	if (c->map.map[x][y] == 'N')
	{
		c->player.dir.y = -1;
		c->player.plane.x = 0.66;
	}
	if (c->map.map[x][y] == 'S')
	{
		c->player.dir.y = 1;
		c->player.plane.x = -0.66;
	}
	if (c->map.map[x][y] == 'E')
	{
		c->player.dir.x = 1;
		c->player.plane.y = 0.66;
	}
	if (c->map.map[x][y] == 'W')
	{
		c->player.dir.x = -1;
		c->player.plane.y = -0.66;
	}
}

void	validate_start(t_cub3d *cub3d)
{
	int		i;
	int		j;
	t_map	*map;

	map = &cub3d->map;
	i = 0;
	while (i < map->width)
	{
		j = 0;
		while (j < map->height)
		{
			if (map->map[i][j] == 'N'
				|| map->map[i][j] == 'W'
				|| map->map[i][j] == 'E'
				|| map->map[i][j] == 'S')
			{
				get_start(cub3d, i, j);
				return ;
			}
			j++;
		}
		i++;
	}
	exit_error(cub3d, "Map doesn't have a starting point");
}

void	validate(t_cub3d *cub3d)
{
	validate_texture(cub3d);
	validate_map(cub3d);
	validate_start(cub3d);
}
