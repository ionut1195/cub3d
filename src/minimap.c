/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:00:50 by aricholm          #+#    #+#             */
/*   Updated: 2022/06/01 17:50:15 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_arrow(t_cub3d *c)
{
	t_vector	from;
	t_vector	to;
	int			i;
	int			j;

	from = c->player.pos;
	from.x *= MINIMAP;
	from.y *= MINIMAP;
	to = from;
	to.x += MINIMAP * c->player.dir.x;
	to.y += MINIMAP * c->player.dir.y;
	make_line (&c->img, from, to, 0xEEEEEE);
	i = -1;
	while (i < 1)
	{
		j = -1;
		while (j < 1)
			my_pixel_put(&c->img, from.x + i, from.y + j++, 0xEE0000);
		i++;
	}
}

void	print_minimap(t_cub3d *cub3d)
{	
	int			i;
	int			j;

	i = 0;
	while (i / MINIMAP < cub3d->map.width)
	{
		j = 0;
		while (j / MINIMAP < cub3d->map.height)
		{
			if (cub3d->map.map[i / MINIMAP][j / MINIMAP] == '1')
				my_pixel_put(&cub3d->img, i, j, 0x663300);
			else if (cub3d->map.map[i / MINIMAP][j / MINIMAP] == '0')
				my_pixel_put(&cub3d->img, i, j, 0x006600);
			else
				my_pixel_put(&cub3d->img, i, j, 0x000000);
			j++;
		}
		i++;
	}
	draw_arrow(cub3d);
}
