/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 09:57:07 by aricholm          #+#    #+#             */
/*   Updated: 2022/05/11 14:44:44 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h" // might refactor this
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define BUFFER_SIZE 10

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
	int	x;
	int	y;
	int	z;
}	t_vector;

typedef struct s_player {
	t_vector	pos;
	t_vector	v;
	t_vector	cam;
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

typedef struct s_cub3d {
	t_map		*map;
	t_player	*player;
	t_textures	*textures;

}	t_cub3d;


//PARSER
void	parser(t_cub3d *cub3d, const char *file);
t_bool	add_texture(t_textures *textures, const char *line);
t_bool	get_map(t_cub3d *cub3d, const char **lines);

//CLEANUP
void	destroy_lines(char **lines);
#endif /* CUB3D_H */
