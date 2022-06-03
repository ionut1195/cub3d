/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 10:12:41 by aricholm          #+#    #+#             */
/*   Updated: 2022/06/03 10:21:22 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_error(t_cub3d *cub3d, const char *msg)
{
	printf("Error\n%s\n", msg);
	destroy_everything(cub3d);
	exit (1);
}

static void	init_cub3d(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	cub3d->player.pos.x = 0;
	cub3d->player.pos.y = 0;
	cub3d->player.dir.x = 0;
	cub3d->player.dir.y = 0;
	cub3d->player.plane.x = 0;
	cub3d->player.plane.y = 0;
	cub3d->lines = NULL;
	cub3d->map.height = 0;
	cub3d->map.width = 0;
	cub3d->map.map = NULL;
	cub3d->map.flag = FALSE;
	while (i < 4)
	{
		cub3d->textures.wall[i].img = NULL;
		cub3d->textures.wall_str[i++] = NULL;
	}
	cub3d->textures.floor = 0;
	cub3d->textures.ceiling = 0;
	cub3d->textures.flag = EMPTY;
	cub3d->mlx = NULL;
	cub3d->img.img = NULL;
}

void	init_mlx(t_cub3d *c)
{
	c->mlx = mlx_init();
	c->img.img = mlx_new_image(c->mlx, SCREEN_W, SCREEN_H);
	c->img.addr = mlx_get_data_addr(c->img.img, &c->img.bpp,
			&c->img.line_len, &c->img.endian);
	c->win = mlx_new_window(c->mlx, SCREEN_W,
			SCREEN_H, "Cub3D");
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
	init_mlx(&cub3d);
	init_textures(&cub3d);
	mlx_loop_hook(cub3d.mlx, &raycast, &cub3d);
	mlx_hook(cub3d.win, 2, 1L << 0, &handle_key, &cub3d);
	mlx_hook(cub3d.win, 17, 1L << 0, &handle_btnrealease, &cub3d);
	mlx_loop(cub3d.mlx);
	destroy_everything(&cub3d);
	return (0);
}
