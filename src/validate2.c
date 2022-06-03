/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:50:50 by aricholm          #+#    #+#             */
/*   Updated: 2022/06/03 11:53:06 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	starting_point(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (TRUE);
	else
		return (FALSE);
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
