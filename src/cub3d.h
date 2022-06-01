/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 09:57:07 by aricholm          #+#    #+#             */
/*   Updated: 2022/06/01 18:01:45 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h" // might refactor this
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "mlx.h"
# include "keys.h"

# define BUFFER_SIZE 10
# define SCREEN_W 1020
# define SCREEN_H 680
# define MOV_SPEED 0.05
# define ROT_SPEED 0.05
# define MINIMAP 6

typedef enum e_bool { FALSE, TRUE}	t_bool;

typedef enum e_tflag {
	EMPTY	= 0b0000000,
	NORTH	= 0b0000001,
	SOUTH	= 0b0000010,
	EAST	= 0b0000100,
	WEST	= 0b0001000,
	FLOOR	= 0b0010000,
	CEILING	= 0b0100000,
	ERROR	= 0b1000000
}	t_tflag;

typedef enum e_twall {
	T_NORTH	= 2,
	T_SOUTH	= 0,
	T_WEST	= 3,
	T_EAST	= 1,
}	t_twall;

/*		map is indexed from the upper left corner
**		
**		(0,0) > (1,0) > ... > (n,0)
**		 V
**		(0,1) > (1,1) > ... > (n,1)
**		 V
**		...
**		 V
**		(0,m) > (1,m) > ... > (n,m)
*/

typedef struct s_map {
	int		width;
	int		height;
	char	**map;
}	t_map;

typedef struct s_vector {
	double	x;
	double	y;
}	t_vector;

typedef struct s_ray {
	t_bool		hit;
	int			step_x;
	int			step_y;
	int			line_height;
	double		pwd;
	int			side;
	int			draw_start;
	int			draw_end;
	double		side_dist_x;
	double		side_dist_y;
	double		camera_x;
	t_vector	dir;
	t_vector	map;
	t_vector	delta_dist;
}	t_ray;

typedef struct s_player {
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	t_vector	v;
}	t_player;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		img_w;
	int		img_h;
}	t_data;

typedef struct s_textures {
	char			*wall_str[4];
	t_data			wall[4];
	unsigned int	floor;
	unsigned int	ceiling;
	t_tflag			flag;
}	t_textures;

typedef struct s_cub3d {
	char		**lines;
	t_map		map;
	t_player	player;
	t_textures	textures;
	void		*mlx;
	void		*win;
	void		*mapw;
	t_data		img;
}	t_cub3d;

//PARSER
void	parser(t_cub3d *cub3d, const char *file);
t_bool	add_texture(t_textures *textures, const char *line);
t_bool	get_map(t_cub3d *cub3d, const char **lines);

void	validate(t_cub3d *cub3d);
void	validate_closedwalls(t_cub3d *cub3d);
void	validate_texture(t_cub3d *cub3d);

//CLEANUP
void	exit_error(t_cub3d *cub3d, const char *msg);
void	destroy_lines(char **lines);
void	destroy_everything(t_cub3d *cub3d);
//void	clean_close(t_cub3d *cub3d);

//DRAW
void	my_pixel_put(t_data *data, int x, int y, int color);
void	make_line(t_data *data, t_vector from, t_vector to, int color);
int		raycast(t_cub3d *cub);
int		get_tex_color(t_data *t, int x, int y);
void	print_minimap(t_cub3d *cub3d);

//ENGINE
void	init_textures(t_cub3d *cub3d);
int		keypress(int key, t_cub3d *cub3d);
int		handle_key(int key, t_cub3d *c);
int		handle_btnrealease(t_cub3d *c);
int		move(int key, t_cub3d *cub);

#endif /* CUB3D_H */
