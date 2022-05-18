/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 10:22:30 by aricholm          #+#    #+#             */
/*   Updated: 2022/05/18 12:14:24 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_texture(t_cub3d *cub3d)
{
(void) cub3d;
	return ;
}

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

	map = cub3d->map;
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

void	validate(t_cub3d *cub3d)
{
	validate_texture(cub3d);
	validate_map(cub3d);
}
