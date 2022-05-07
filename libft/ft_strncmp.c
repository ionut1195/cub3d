/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 21:01:38 by aricholm          #+#    #+#             */
/*   Updated: 2021/12/14 10:09:48 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	i = 0;
	ptr1 = (void *)str1;
	ptr2 = (void *)str2;
	while (i < n && (ptr1[i] || ptr2[i]))
	{
		if (ptr1[i] - ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}
