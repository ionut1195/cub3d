/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 18:43:43 by aricholm          #+#    #+#             */
/*   Updated: 2021/12/14 10:09:51 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*big, const char *smol, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!smol[0])
		return ((char *)big);
	while (i < len && big[i])
	{
		j = 0;
		while (big[i + j] == smol[j] && (i + j < len) && smol[j] && big[i + j])
		{
			j++;
			if (!smol[j])
				return ((char *)&big[i]);
		}
		i++;
	}
	return (0);
}
