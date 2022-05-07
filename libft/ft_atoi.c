/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 19:53:01 by aricholm          #+#    #+#             */
/*   Updated: 2021/05/12 20:48:35 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (c);
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		count;
	int		negative;

	i = 0;
	negative = 1;
	count = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			negative = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		count = count * 10;
		count += str[i] - '0';
		i++;
	}
	return (count * negative);
}
