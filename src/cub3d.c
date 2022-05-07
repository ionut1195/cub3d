/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 10:12:41 by aricholm          #+#    #+#             */
/*   Updated: 2022/05/07 12:37:44 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
static void	init_player(t_player *player)
{
	player->pos.x = 0;
	player->pos.y = 0;
	player->pos.z = 0;
	player->cam.x = 0;
	player->cam.y = 0;
	player->cam.z = 0;
	player->v.x = 0;
	player->v.y = 0;
	player->v.z = 0;
}*/

static void	init_cub3d(t_cub3d *cub3d)
{
	cub3d->player->pos.x = 0;
	cub3d->player->pos.y = 0;
	cub3d->player->pos.z = 0;
	cub3d->player->cam.x = 0;
	cub3d->player->cam.y = 0;
	cub3d->player->cam.z = 0;
	cub3d->player->v.x = 0;
	cub3d->player->v.y = 0;
	cub3d->player->v.z = 0;
	cub3d->map->height = 0;
	cub3d->map->width = 0;
	cub3d->map->map = NULL;
	cub3d->textures->north = NULL;
	cub3d->textures->south = NULL;
	cub3d->textures->east = NULL;
	cub3d->textures->west = NULL;
	cub3d->textures->floor = 0;
	cub3d->textures->ceiling = 0;
}

int	main(int argc, char const *argv[])
{
	t_cub3d		cub3d;
	t_map		map;
	t_player	player;
	t_textures	textures;

	if (argc != 2)
	{
		printf("usage:\n./cub3d <mapname.cub>\n");
		return (0);
	}
	cub3d.player = &player;
	cub3d.map = &map;
	cub3d.textures = &textures;
	init_cub3d(&cub3d);
	parser(&cub3d, argv[1]);

	return (0);
}
