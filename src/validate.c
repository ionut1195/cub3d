/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 10:22:30 by aricholm          #+#    #+#             */
/*   Updated: 2022/05/17 13:04:02 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_texture(t_cub3d *cub3d)
{
	(void) cub3d;
	return ;
}

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
			{
				printf("Error\n%c: Invalid map object\n", map->map[i][j]);
				destroy_everything(cub3d);
				exit (1);
			}
			j++;
		}
		i++;
	}
}

void	validate(t_cub3d *cub3d)
{
	validate_texture(cub3d);
	validate_map(cub3d);
	validate_closedwalls(cub3d);
}
