/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 22:42:50 by aricholm          #+#    #+#             */
/*   Updated: 2021/06/08 12:19:09 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcut(char *s, char c, size_t off)
{
	size_t	i;
	char	*tmp;

	if (!s)
		return (0);
	if (!c)
		return (s);
	i = off;
	while (s[i] == c && s[i])
		i++;
	tmp = ft_substr(s, i, ft_strlen(s) - i);
	free (s);
	return (tmp);
}

static size_t	ft_splitcount(char *s, char c)
{
	size_t	i;
	size_t	count;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		while (s[i] == c && s[i])
			i++;
	}
	return (count);
}

static char	**ft_purge(char **arr, char *str)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free (arr[i++]);
	if (arr)
		free (arr);
	if (str)
		free (str);
	return (0);
}

static size_t	ft_geti(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	*str;
	char	**out;
	size_t	i;
	size_t	j;
	size_t	count;

	if (!s)
		return (0);
	str = ft_strcut(ft_strdup(s), c, 0);
	count = ft_splitcount(str, c);
	out = malloc((count + 1) * sizeof(char *));
	if (!out || !str)
		return (ft_purge(out, str));
	j = 0;
	while (j < count)
	{
		i = ft_geti(str, c);
		out[j] = ft_substr(str, 0, i);
		str = ft_strcut(str, c, i);
		if (!out[j++] || !str)
			return (ft_purge(out, str));
	}
	out[j] = 0;
	free (str);
	return (out);
}
