/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 21:05:25 by aricholm          #+#    #+#             */
/*   Updated: 2021/12/14 10:05:39 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;
	char	*ptr;
	char	*ptr2;

	i = 0;
	ptr = dest;
	ptr2 = (void *)src;
	while (i < n)
	{
		ptr[i] = ptr2[i];
		if ((unsigned char)ptr2[i] == (unsigned char)c)
			return (&ptr[i + 1]);
		i++;
	}
	return (0);
}
