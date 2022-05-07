/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 22:30:48 by aricholm          #+#    #+#             */
/*   Updated: 2021/12/14 10:09:07 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_ilen(int n)
{
	size_t	len;
	int		num;

	len = 0;
	num = n;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (num != 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

static int	ft_strip(int i, int n)
{
	while (i > 1)
	{
		n = n / 10;
		i--;
	}
	return (n % 10);
}

void	ft_putnbr_fd(int n, int fd)
{
	size_t	len;
	char	c;

	if (n == -2147483648)
	{
		c = '-';
		write(fd, &c, 1);
		c = '2';
		write(fd, &c, 1);
		n = 147483648;
	}
	if (n < 0)
	{
		c = '-';
		write(fd, &c, 1);
		n = -n;
	}
	len = ft_ilen(n);
	while (len)
	{
		c = ft_strip(len, n) + '0';
		write(fd, &c, 1);
		len--;
	}
}
