/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:16:35 by aroullea          #+#    #+#             */
/*   Updated: 2024/10/19 17:32:51 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static t_list	*ft_sort(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*start_map;
	void	*cont;

	map = NULL;
	start_map = NULL;
	while (lst)
	{
		cont = f(lst->content);
		if (!cont)
		{
			ft_lstclear(&start_map, del);
			return (NULL);
		}
		map = ft_lstnew(cont);
		if (!map)
		{
			del(cont);
			ft_lstclear(&start_map, del);
			return (NULL);
		}
		ft_lstadd_back(&start_map, map);
		lst = lst->next;
	}
	return (start_map);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;

	if (!lst || !f || !del)
		return (NULL);
	res = ft_sort(lst, f, del);
	return (res);
}
