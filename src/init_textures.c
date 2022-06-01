/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 12:07:42 by aricholm          #+#    #+#             */
/*   Updated: 2022/06/01 20:27:07 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(int x, t_ray *ray, t_player *player)
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

void	validate_texture(t_cub3d *cub3d)
{
	t_textures	*t;
	int			i;

	i = 0;
	t = &cub3d->textures;
	while (i < 4)
	{
		if (ft_strncmp(&t->wall_str[i][ft_strlen(t->wall_str[i]) - 4],
			".xpm", 4))
			exit_error(cub3d, "Texture is not a .xpm file");
		i++;
	}
}

int	get_tex_color(t_data *t, int x, int y)
{
	int	color;

	if (x < 0 || x >= t->img_w || y < 0 || y >= t->img_h)
		return (0);
	color = *(unsigned int *)(t->addr + y * t->line_len + x * (t->bpp / 8));
	return (color);
}

void	init_textures(t_cub3d *cub3d)
{
	t_textures	*t;
	int			i;

	i = 0;
	t = &cub3d->textures;
	while (i < 4)
	{
		t->wall[i].img = mlx_xpm_file_to_image(cub3d->mlx, t->wall_str[i],
				&t->wall[i].img_w, &t->wall[i].img_h);
		if (!t->wall[i].img)
			exit_error(cub3d, "Couldn't read texture file");
		t->wall[i].addr = mlx_get_data_addr(t->wall[i].img, &t->wall[i].bpp,
				&t->wall[i].line_len, &t->wall[i].endian);
		i++;
	}
}
