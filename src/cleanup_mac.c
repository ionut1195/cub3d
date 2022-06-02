/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_mac.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:43:33 by aricholm          #+#    #+#             */
/*   Updated: 2022/06/01 20:27:40 by aricholm         ###   ########.fr       */
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
	free (texture->wall_str[0]);
	free (texture->wall_str[1]);
	free (texture->wall_str[2]);
	free (texture->wall_str[3]);
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

static void	destroy_mlx(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub3d->textures.wall[i].img)
			mlx_destroy_image(cub3d->mlx, cub3d->textures.wall[i].img);
		i++;
	}
	if (cub3d->img.img)
		mlx_destroy_image(cub3d->mlx, cub3d->img.img);
	mlx_destroy_window(cub3d->mlx, cub3d->win);
	free(cub3d->mlx);
}

void	destroy_everything(t_cub3d *cub3d)
{
	destroy_lines(cub3d->lines);
	cub3d->lines = NULL;
	destroy_map(&cub3d->map);
	destroy_texture(&cub3d->textures);
	if (cub3d->mlx)
		destroy_mlx(cub3d);
}
