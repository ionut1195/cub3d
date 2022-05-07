/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 21:20:04 by aricholm          #+#    #+#             */
/*   Updated: 2021/12/14 10:09:55 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_isset(char c, char const *set)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = (void *)set;
	while (ptr[i])
	{
		if (ptr[i] == c)
			return (ptr[i]);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	i;
	size_t	len;

	if (!s1)
		return (0);
	len = ft_strlen(s1);
	i = 0;
	while (ft_isset(((char *)s1)[i], set) && i < len)
		i++;
	while (ft_isset(((char *)s1)[len - 1], set) && len > 0)
		len--;
	if (i > len)
		i = 0;
	new = ft_substr(s1, i, len - i);
	return (new);
}
