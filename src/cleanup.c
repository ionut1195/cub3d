/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itomescu <itomescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:43:33 by aricholm          #+#    #+#             */
/*   Updated: 2022/05/28 19:00:10 by itomescu         ###   ########.fr       */
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

static void destroy_mlx(t_cub3d *cub3d)
{
	mlx_destroy_image(cub3d->mlx, cub3d->wall.img);
	mlx_destroy_image(cub3d->mlx, cub3d->smth.img);
	mlx_destroy_image(cub3d->mlx, cub3d->empty.img);
	mlx_destroy_image(cub3d->mlx, cub3d->img.img);
	mlx_destroy_image(cub3d->mlx, cub3d->textures.no.img);
	mlx_destroy_image(cub3d->mlx, cub3d->textures.so.img);
	mlx_destroy_image(cub3d->mlx, cub3d->textures.ea.img);
	mlx_destroy_image(cub3d->mlx, cub3d->textures.we.img);
	mlx_destroy_window(cub3d->mlx, cub3d->win);
	mlx_destroy_window(cub3d->mlx, cub3d->mapw);
	// mlx_destroy_display(cub3d->mlx);
	// mlx_loop_end(cub3d->mlx);
	free(cub3d->mlx);
}

void	destroy_everything(t_cub3d *cub3d)
{
	destroy_lines(cub3d->lines);
	cub3d->lines = NULL;
	destroy_map(&cub3d->map);
	destroy_texture(&cub3d->textures);
	destroy_mlx(cub3d);
}

void	clean_close(t_cub3d *cub3d)
{
	destroy_everything(cub3d);
	mlx_destroy_image(cub3d->mlx, cub3d->wall.img);
	mlx_destroy_image(cub3d->mlx, cub3d->smth.img);
	mlx_destroy_image(cub3d->mlx, cub3d->empty.img);
	mlx_destroy_image(cub3d->mlx, cub3d->img.img);
	mlx_destroy_window(cub3d->mlx, cub3d->win);
	mlx_destroy_window(cub3d->mlx, cub3d->mapw);
	// mlx_destroy_display(cub3d->mlx);
	// mlx_loop_end(cub3d->mlx);
	free(cub3d->mlx);
	exit (EXIT_FAILURE);
}
