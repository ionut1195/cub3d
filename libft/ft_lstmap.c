/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aricholm <aricholm@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 11:15:50 by aricholm          #+#    #+#             */
/*   Updated: 2021/06/08 11:38:24 by aricholm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*tmp;
	t_list	*new;

	if (!lst || !(*f) || !(*del))
		return (0);
	new = ft_lstnew(f(lst->content));
	if (!new)
		return (0);
	first = new;
	tmp = lst->next;
	while (tmp)
	{
		new->next = ft_lstnew(f(tmp->content));
		if (!new->next)
		{
			ft_lstclear(&first, del);
			return (0);
		}
		new = new->next;
		tmp = tmp->next;
	}
	new->next = 0;
	return (first);
}
