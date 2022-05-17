/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:12:51 by aricholm          #+#    #+#             */
/*   Updated: 2022/05/11 11:10:05 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	t_tflag	get_flag(const char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (NORTH);
	if (!ft_strncmp(line, "SO ", 3))
		return (SOUTH);
	if (!ft_strncmp(line, "EA ", 3))
		return (EAST);
	if (!ft_strncmp(line, "WE ", 3))
		return (WEST);
	if (!ft_strncmp(line, "C ", 2))
		return (CEILING);
	if (!ft_strncmp(line, "F ", 2))
		return (FLOOR);
	return (ERROR);
}

static int	get_subcolor(const char *line, int *i)
{
	int	subcolor;

	subcolor = 0;
	while (line[*i] == ' ')
		(*i)++;
	if (!ft_isdigit(line[*i]))
		return (-1);
	while (ft_isdigit(line[*i]))
		subcolor = subcolor * 10 + line[(*i)++] - '0';
	if (subcolor > 255)
		return (-1);
	while (line[*i] == ' ')
		(*i)++;
	return (subcolor);
}

static int	str2color(const char *line)
{
	int	color;
	int	subcolor;
	int	i;
	int	j;

	color = 0;
	i = 0;
	j = 0;
	while (j < 3)
	{
		subcolor = get_subcolor(line, &i);
		if (subcolor == -1)
			return (-1);
		color = (color << 8) + subcolor;
		if (j < 2 && line[i++] != ',')
			return (-1);
		j++;
	}
	if (line[i])
		return (-1);
	return (color);
}

static t_bool	add_texture2(	t_textures *textures,
								const char *line,
								t_tflag flag)
{
	int	color;

	if (flag == FLOOR)
	{	
		color = str2color(&line[2]);
		if (color == -1)
			return (FALSE);
		textures->floor = color;
	}
	if (flag == CEILING)
	{
		color = str2color(&line[2]);
		if (color == -1)
			return (FALSE);
		textures->ceiling = color;
	}
	return (TRUE);
}

t_bool	add_texture(t_textures *textures, const char *line)
{
	t_tflag	flag;

	flag = get_flag(line);
	if (flag & textures->flag || flag == ERROR)
		return (FALSE);
	textures->flag |= flag;
	if (flag == CEILING || flag == FLOOR)
		return (add_texture2(textures, line, flag));
	if (flag == NORTH)
		textures->north = ft_strtrim(&line[3], " \t\n\v\f\r");
	if (flag == SOUTH)
		textures->south = ft_strtrim(&line[3], " \t\n\v\f\r");
	if (flag == EAST)
		textures->east = ft_strtrim(&line[3], " \t\n\v\f\r");
	if (flag == WEST)
		textures->west = ft_strtrim(&line[3], " \t\n\v\f\r");
	return (TRUE);
}
