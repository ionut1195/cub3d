/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:28:37 by aricholm          #+#    #+#             */
/*   Updated: 2022/06/03 09:26:46 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
int	keypress(int key, t_cub3d *cub3d)
{
	if (key == 65307)
		clean_close(cub3d);
	return (0);
}*/

int	handle_key(int key, t_cub3d *c)
{
	if (key == KEY_ESC)
	{
		destroy_everything(c);
		exit(0);
	}
	else
		move(key, c);
	return (0);
}

int	handle_btnrealease(t_cub3d *c)
{
	destroy_everything(c);
	exit(0);
	return (0);
}
