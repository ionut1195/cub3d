/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 09:57:07 by aricholm          #+#    #+#             */
/*   Updated: 2022/05/07 12:36:14 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h" // might refactor this
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>

typedef enum e_bool { FALSE, TRUE}	t_bool;

typedef struct s_map {
	unsigned int	width;
	unsigned int	height;
	int				**map;
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
}	t_textures;

typedef struct s_cub3d {
	t_map		*map;
	t_player	*player;
	t_textures	*textures;

}	t_cub3d;

void	parser(t_cub3d *cub3d, const char *file);

#endif /* CUB3D_H */
