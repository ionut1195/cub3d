/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 10:12:41 by aricholm          #+#    #+#             */
/*   Updated: 2022/05/28 13:36:28 by aricholm         ###   ########.fr       */
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
void	exit_error(t_cub3d *cub3d, const char *msg)
{
	printf("Error\n%s\n", msg);
	destroy_everything(cub3d);
	exit (1);
}

static void	init_cub3d(t_cub3d *cub3d)
{
	cub3d->player.pos.x = 0;
	cub3d->player.pos.y = 0;
//	cub3d->player.pos.z = 0;
	cub3d->player.dir.x = 0;
	cub3d->player.dir.y = 0;
//	cub3d->player.dir.z = 0;
	cub3d->player.plane.x = 0;
	cub3d->player.plane.y = 0;
//	cub3d->player.plane.z = 0;
	cub3d->player.v.x = 0;
	cub3d->player.v.y = 0;
//	cub3d->player.v.z = 0;
	cub3d->lines = NULL;
	cub3d->map.height = 0;
	cub3d->map.width = 0;
	cub3d->map.map = NULL;
	cub3d->textures.north = NULL;
	cub3d->textures.south = NULL;
	cub3d->textures.east = NULL;
	cub3d->textures.west = NULL;
	cub3d->textures.floor = 0;
	cub3d->textures.ceiling = 0;
	cub3d->textures.flag = EMPTY;
}

void	init_mlx(t_cub3d *c)
{
	c->mlx = mlx_init();
	c->img.img = mlx_new_image(c->mlx, SCREEN_W, SCREEN_H);
	c->img.addr = mlx_get_data_addr(c->img.img, &c->img.bpp,
			&c->img.line_len, &c->img.endian);

	c->win = mlx_new_window(c->mlx, SCREEN_W,
			SCREEN_H, "Cub3D");
	c->mapw = mlx_new_window(c->mlx, c->map.width * 30,
			c->map.height * 30, "Cub3D map");
	c->wall.img = mlx_xpm_file_to_image(c->mlx, "img/green.xpm",
			&c->wall.img_w, &c->wall.img_h);
	c->empty.img = mlx_xpm_file_to_image(c->mlx, "img/black.xpm",
			&c->empty.img_w, &c->empty.img_h);
	c->smth.img = mlx_xpm_file_to_image(c->mlx, "img/blue.xpm",
			&c->smth.img_w, &c->smth.img_h);
}

int	printminimap(t_cub3d *cub)
{
	int			row;
	int			col;

	row = 0;
	if (cub->win == NULL)
		return (1);
	while (row < cub->map.height)
	{
		col = 0;
		while (col < cub->map.width)
		{
			if (cub->map.map[col][row] == '1')
				mlx_put_image_to_window(cub->mlx, cub->mapw,
					cub->wall.img, (col * cub->wall.img_h),
					(row * cub->wall.img_w));
			else if (cub->map.map[col][row] == '0')
				mlx_put_image_to_window(cub->mlx, cub->mapw,
					cub->smth.img, (col * cub->empty.img_h),
					(row * cub->empty.img_w));
			col++;
		}
		row++;
	}
	mlx_pixel_put(cub->mlx, cub->mapw, cub->player.pos.x * 30, cub->player.pos.y * 30, 0xEEEEEE);
	mlx_pixel_put(cub->mlx, cub->mapw, cub->player.pos.x * 30 + cub->player.dir.x * 5,
			cub->player.pos.y * 30 + cub->player.dir.y * 5, 0xEE0000);
	return (0);
}

int	main(int argc, char const *argv[])
{
	t_cub3d		cub3d;

	if (argc != 2)
	{
		printf("usage:\n%s <mapname.cub>\n", argv[0]);
		return (0);
	}
	init_cub3d(&cub3d);
	parser(&cub3d, argv[1]);
	validate(&cub3d);
// WIP 
	init_mlx(&cub3d);

	printminimap(&cub3d);
	mlx_loop_hook(cub3d.mlx, &raycast, &cub3d);
	mlx_loop(cub3d.mlx);

	destroy_everything(&cub3d);
	return (0);
}
