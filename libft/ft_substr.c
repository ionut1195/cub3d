/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 10:10:23 by aricholm          #+#    #+#             */
/*   Updated: 2021/12/14 10:09:58 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*src;
	char	*dst;

	if (!s)
		return (0);
	i = 0;
	src = (void *)s;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	dst = malloc(len + 1);
	if (!dst)
		return (0);
	while (i < len)
	{
		dst[i] = src[start + i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}
