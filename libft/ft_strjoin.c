/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 21:18:40 by aricholm          #+#    #+#             */
/*   Updated: 2021/12/14 10:09:36 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	i;
	size_t	len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1);
	dst = malloc(len + ft_strlen(s2) + 1);
	if (!dst)
		return (0);
	i = 0;
	while (i < len)
	{
		dst[i] = ((char *)s1)[i];
		i++;
	}
	i = 0;
	while (((char *)s2)[i])
	{
		dst[len + i] = ((char *)s2)[i];
		i++;
	}
	dst[len + i] = 0;
	return (dst);
}
