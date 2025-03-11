/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 06:13:08 by aroullea          #+#    #+#             */
/*   Updated: 2024/10/18 10:26:58 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*last;

	if (!lst || !del)
		return ;
	while (*lst != NULL)
	{
		last = *lst;
		del(last->content);
		*lst = last->next;
		free(last);
	}
	*lst = NULL;
}
