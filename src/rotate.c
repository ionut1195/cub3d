/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:22:47 by aricholm          #+#    #+#             */
/*   Updated: 2022/06/01 18:23:17 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_cub3d *c)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = c->player.dir.x;
	c->player.dir.x = c->player.dir.x * cos(-ROT_SPEED)
		- c->player.dir.y * sin(-ROT_SPEED);
	c->player.dir.y = old_dir_x * sin(-ROT_SPEED)
		+ c->player.dir.y * cos(-ROT_SPEED);
	old_plane_x = c->player.plane.x;
	c->player.plane.x = c->player.plane.x * cos(-ROT_SPEED)
		- c->player.plane.y * sin(-ROT_SPEED);
	c->player.plane.y = old_plane_x * sin(-ROT_SPEED)
		+ c->player.plane.y * cos(-ROT_SPEED);
}

void	rotate_right(t_cub3d *c)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = c->player.dir.x;
	c->player.dir.x = c->player.dir.x * cos(ROT_SPEED)
		- c->player.dir.y * sin(ROT_SPEED);
	c->player.dir.y = old_dir_x * sin(ROT_SPEED)
		+ c->player.dir.y * cos(ROT_SPEED);
	old_plane_x = c->player.plane.x;
	c->player.plane.x = c->player.plane.x * cos(ROT_SPEED)
		- c->player.plane.y * sin(ROT_SPEED);
	c->player.plane.y = old_plane_x * sin(ROT_SPEED)
		+ c->player.plane.y * cos(ROT_SPEED);
}
