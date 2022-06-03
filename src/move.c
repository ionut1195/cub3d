/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 18:39:19 by aricholm          #+#    #+#             */
/*   Updated: 2022/06/03 10:27:23 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_up(t_cub3d *c)
{
	if (c->map.map[(int)(c->player.pos.x
			+ c->player.dir.x * MOV_SPEED)][(int)c->player.pos.y] != '1')
		c->player.pos.x += c->player.dir.x * MOV_SPEED;
	if (c->map.map[(int)c->player.pos.x][(int)(c->player.pos.y
		+ c->player.dir.y * MOV_SPEED)] != '1')
		c->player.pos.y += c->player.dir.y * MOV_SPEED;
}

static void	move_down(t_cub3d *c)
{
	if (c->map.map[(int)(c->player.pos.x - c->player.dir.x
			* MOV_SPEED)][(int)c->player.pos.y] != '1')
		c->player.pos.x -= c->player.dir.x * MOV_SPEED;
	if (c->map.map[(int)c->player.pos.x][(int)(c->player.pos.y - c->player.dir.y
		* MOV_SPEED)] != '1')
		c->player.pos.y -= c->player.dir.y * MOV_SPEED;
}

static void	move_left(t_cub3d *c)
{
	if (c->map.map[(int)(c->player.pos.x - c->player.plane.x
			* MOV_SPEED)][(int)c->player.pos.y] != '1')
		c->player.pos.x -= c->player.plane.x * MOV_SPEED;
	if (c->map.map[(int)c->player.pos.x][(int)(c->player.pos.y
		- c->player.plane.y * MOV_SPEED)] != '1')
		c->player.pos.y -= c->player.plane.y * MOV_SPEED;
}

static void	move_right(t_cub3d *c)
{
	if (c->map.map[(int)(c->player.pos.x + c->player.plane.x
			* MOV_SPEED)][(int)c->player.pos.y] != '1')
		c->player.pos.x += c->player.plane.x * MOV_SPEED;
	if (c->map.map[(int)c->player.pos.x][(int)(c->player.pos.y
		+ c->player.plane.y * MOV_SPEED)] != '1')
		c->player.pos.y += c->player.plane.y * MOV_SPEED;
}

int	move(int key, t_cub3d *cub)
{
	if (key == KEY_W || key == KEY_UP)
		move_up(cub);
	else if (key == KEY_S || key == KEY_DOWN)
		move_down(cub);
	else if (key == KEY_A)
		move_left(cub);
	else if (key == KEY_D)
		move_right(cub);
	else if (key == KEY_LEFT)
		rotate_left(cub);
	else if (key == KEY_RIGHT)
		rotate_right(cub);
	return (0);
}
