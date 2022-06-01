/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itomescu <itomescu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:13:15 by aricholm          #+#    #+#             */
/*   Updated: 2022/06/01 15:07:04 by itomescu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(int x, t_ray *ray, t_player *player)
{
	ray->camera_x = 2 * x / (double)SCREEN_W - 1;
	ray->map.x = (int)player->pos.x;
	ray->map.y = (int)player->pos.y;
	ray->hit = FALSE;
	ray->line_height = 0;
	ray->pwd = 0.0;
	ray->side = 0;
	ray->dir.x = player->dir.x + player->plane.x * ray->camera_x;
	ray->dir.y = player->dir.y + player->plane.y * ray->camera_x;
	if (ray->dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1 / ray->dir.y);
}

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
	int	color;
	int	i;
	t_data	*tex;
	int	tex_x;
	int	tex_y = 0;
  double wall_x;
  double tex_pos;
  double step;

	i = 0;
	tex = &cub->textures.wall[ray->side];
	color = 0xcd5c5c;
	color -= ray->side * 100;
  if (ray->side == 0)
    wall_x = cub->player.pos.y + ray->pwd * ray->dir.y;
  else
    wall_x = cub->player.pos.x + ray->pwd * ray->dir.x;
  wall_x -= floor(wall_x);
  
  tex_x = (int)(wall_x * (double)TEX_W);
  // if (ray->side == 0 && ray->dir.x > 0)
  //   tex_x = TEX_W - tex_x - 1;
  // if ((ray->side == 1 || ray->side == 2 || ray->side == 3) && ray->dir.y < 0)
  //   tex_x = TEX_W - tex_x - 1;
  step = 1.0 * TEX_H / ray->line_height;
  tex_pos = (ray->draw_start - SCREEN_H / 2 + ray->line_height / 2) *step;
	while (i < ray->draw_start)
		my_pixel_put(&cub->img, x, i++, cub->textures.ceiling);
	while (i < ray->draw_end)
	{
		// tex_x = x % tex->img_w;//tex->img_w * (fmod(ray->map.x, 1.0) + fmod(ray->map.y, 1.0));
    tex_x = TEX_W - tex_x - 1;
		tex_y = tex->img_h * ((double)(i - (-ray->line_height / 2 + SCREEN_H / 2)) / (double)ray->line_height);
    // tex_y = (int)cub->player.pos.x & (TEX_H - 1);
    // tex_pos += step;
		my_pixel_put(&cub->img, x, i,
			get_tex_color(tex, tex_x, tex_y));
		i++;
	}
//		my_pixel_put(&cub->img, x, i++, color);
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
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img.img, 0, 0);
	return (0);
}
