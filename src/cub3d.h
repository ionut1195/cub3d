/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 09:57:07 by aricholm          #+#    #+#             */
/*   Updated: 2022/05/28 13:11:01 by aricholm         ###   ########.fr       */
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
# include "../mlx/mlx.h"

# define BUFFER_SIZE 10
# define SCREEN_W 640
# define SCREEN_H 480

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

// typedef enum e_mapobject {
// 	EMPTY	= 0,
// 	WALL	= 1,
// 	N	= 2,
// 	S	= 3,
// 	E	= 4,
// 	W	= 5
// }	t_mapobject;

typedef struct s_map {
	int		width;
	int		height;
	char	**map;
}	t_map;

typedef struct s_vector {
	double	x;
	double	y;
//	int	z;
}	t_vector;

typedef struct s_img {
	void	*img;
	int		img_w;
	int		img_h;
}	t_img;

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

typedef struct s_textures {
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	unsigned int	floor;
	unsigned int	ceiling;
	t_tflag			flag;
}	t_textures;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_data;

typedef struct s_mlx {
	void	*mlx;
	void	*window;
	t_data	*curr;
	t_data	*next;
}	t_mlx;

typedef struct s_cub3d {
	char		**lines;
	t_map		map;
	t_player	player;
	t_textures	textures;
	void		*mlx;
	void		*win;
	void		*mapw;
	t_data		img;
	t_img		wall;
	t_img		empty;
	t_img		smth;
}	t_cub3d;


//PARSER
void	parser(t_cub3d *cub3d, const char *file);
t_bool	add_texture(t_textures *textures, const char *line);
t_bool	get_map(t_cub3d *cub3d, const char **lines);

void	validate(t_cub3d *cub3d);
void	validate_closedwalls(t_cub3d *cub3d);

//CLEANUP
void	exit_error(t_cub3d *cub3d, const char *msg);
void	destroy_lines(char **lines);
void	destroy_everything(t_cub3d *cub3d);

//DRAW
void	make_line(t_data *data, t_vector from, t_vector to, int color);
int		raycast(t_cub3d *cub);
#endif /* CUB3D_H */
