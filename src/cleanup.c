/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:43:33 by aricholm          #+#    #+#             */
/*   Updated: 2022/05/28 13:00:37 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_lines(char **lines)
{
	int	i;

	i = 0;
	if (!lines)
		return ;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}

static void	destroy_texture(t_textures *texture)
{
	if (texture->north)
		free(texture->north);
	if (texture->south)
		free(texture->south);
	if (texture->west)
		free(texture->west);
	if (texture->east)
		free(texture->east);
}

static void	destroy_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map->map)
		return ;
	while (i < map->width)
		free(map->map[i++]);
	free(map->map);
}

void	destroy_everything(t_cub3d *cub3d)
{
	destroy_lines(cub3d->lines);
	cub3d->lines = NULL;
	destroy_map(&cub3d->map);
	destroy_texture(&cub3d->textures);
}
