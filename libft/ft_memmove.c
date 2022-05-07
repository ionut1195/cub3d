/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 21:05:58 by aricholm          #+#    #+#             */
/*   Updated: 2021/12/14 10:08:16 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*ptr;

	if (!dest && !src && n)
		return (0);
	ptr = dest;
	if (ptr < (char *)src)
	{
		i = 0;
		while (i < n)
		{
			ptr[i] = ((char *)src)[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			ptr[i - 1] = ((char *)src)[i - 1];
			i--;
		}
	}
	return (dest);
}
