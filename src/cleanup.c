/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:43:33 by aricholm          #+#    #+#             */
/*   Updated: 2022/05/11 11:25:19 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_lines(char **lines)
{
	int	i;

	if (!lines)
		return ;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}
