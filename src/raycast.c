/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:13:15 by aricholm          #+#    #+#             */
/*   Updated: 2022/06/01 18:28:39 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* INIT_RAY MOVED TO INIT_TEXTURES.C BECAUSE OF NORMINETTE... */

static void	set_step(t_ray *ray, t_player *p)
{
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (p->pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map.x + 1.0 - p->pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (p->pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map.y + 1.0 - p->pos.y) * ray->delta_dist.y;
	}
}

static void	run_dda(t_ray *ray, t_cub3d *cub)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist.x;
			ray->map.x += ray->step_x;
			if (ray->step_x >= 0)
				ray->side = 1;
			else
				ray->side = 3;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist.y;
			ray->map.y += ray->step_y;
			if (ray->step_y >= 0)
				ray->side = 0;
			else
				ray->side = 2;
		}
		if (cub->map.map[(int)(ray->map.x)][(int)ray->map.y] == '1')
			ray->hit = TRUE;
	}
}

static void	calculate_ray(t_ray *ray)
{
	ray->draw_end = 0;
	ray->draw_start = 0;
	if (ray->side % 2)
		ray->pwd = ray->side_dist_x - ray->delta_dist.x;
	else
		ray->pwd = ray->side_dist_y - ray->delta_dist.y;
	if (ray->pwd < 0.01)
		ray->pwd = 0.01;
	ray->line_height = (int)(SCREEN_H / ray->pwd);
	ray->draw_start = (-ray->line_height / 2 + SCREEN_H / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2 + SCREEN_H / 2);
	if (ray->draw_end >= SCREEN_H)
		ray->draw_end = SCREEN_H - 1;
}

static void	draw_it(int x, t_ray *ray, t_cub3d *cub)
{
	int		i;
	t_data	*tex;
	int		tex_x;
	int		tex_y;

	i = 0;
	tex = &cub->textures.wall[ray->side];
	while (i < ray->draw_start)
		my_pixel_put(&cub->img, x, i++, cub->textures.ceiling);
	while (i < ray->draw_end)
	{
		if (ray->side % 2)
			tex_x = tex->img_w * (cub->player.pos.y + ray->pwd * ray->dir.y
					- floor(cub->player.pos.y + ray->pwd * ray->dir.y));
		else
			tex_x = tex->img_w * (cub->player.pos.x + ray->pwd * ray->dir.x
					- floor(cub->player.pos.x + ray->pwd * ray->dir.x));
		tex_y = tex->img_h * ((double)(i + (ray->line_height - SCREEN_H) / 2)
				/ ray->line_height);
		my_pixel_put(&cub->img, x, i,
			get_tex_color(tex, tex_x, tex_y));
		i++;
	}
	while (i < SCREEN_H)
		my_pixel_put(&cub->img, x, i++, cub->textures.floor);
}

int	raycast(t_cub3d *cub3d)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < SCREEN_W)
	{
		init_ray(x, &ray, &cub3d->player);
		set_step(&ray, &cub3d->player);
		run_dda(&ray, cub3d);
		calculate_ray(&ray);
		draw_it(x, &ray, cub3d);
		x++;
	}
	print_minimap(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img.img, 0, 0);
	return (0);
}
