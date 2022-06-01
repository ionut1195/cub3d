/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 14:03:30 by aricholm          #+#    #+#             */
/*   Updated: 2022/06/01 17:33:32 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (y >= 0 && y < SCREEN_H && x >= 0 && x < SCREEN_W)
	{
		dst = data->addr + (y * data->line_len + x *(data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

static void	swap_coordinates(t_vector *c1, t_vector *c2)
{
	int	tmp;

	tmp = c1->x;
	c1->x = c2->x;
	c2->x = tmp;
	tmp = c1->y;
	c1->y = c2->y;
	c2->y = tmp;
}

static void	make_line_x(t_data *data, t_vector from, t_vector to, int color)
{
	int		x;
	int		y;
	double	slope;

	x = from.x;
	y = from.y;
	if ((to.x - from.x) == 0)
		slope = 1;
	else
		slope = (double)(to.y - from.y) / (double)(to.x - from.x);
	while (x != (int)to.x)
	{
		my_pixel_put(data, x, y, color);
		x++;
		if (slope > 0 && ((from.y + (x - from.x) * slope) > y + 0.5))
			y++;
		if (slope < 0 && ((from.y + (x - from.x) * slope) < y - 0.5))
			y--;
	}
}

static void	make_line_y(t_data *data, t_vector from, t_vector to, int color)
{
	int		x;
	int		y;
	double	slope;

	x = from.x;
	y = from.y;
	if ((to.y - from.y) == 0)
		slope = 1;
	else
		slope = (double)(to.x - from.x) / (double)(to.y - from.y);
	while (y != (int)to.y)
	{
		my_pixel_put(data, x, y, color);
		y++;
		if (slope > 0 && ((from.x + (y - from.y) * slope) > x + 0.5))
			x++;
		if (slope < 0 && ((from.x + (y - from.y) * slope) < x - 0.5))
			x--;
	}
}

void	make_line(t_data *data, t_vector from, t_vector to, int color)
{
	if (fabs(to.x - from.x) > fabs(to.y - from.y))
	{
		if (to.x < from.x)
			swap_coordinates(&from, &to);
		make_line_x(data, from, to, color);
	}
	else
	{
		if (to.y < from.y)
			swap_coordinates(&from, &to);
		make_line_y(data, from, to, color);
	}
}
