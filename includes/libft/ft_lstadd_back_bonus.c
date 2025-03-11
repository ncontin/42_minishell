/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:19:29 by aroullea          #+#    #+#             */
/*   Updated: 2024/10/19 16:13:43 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	else if (lst)
	{
		if (*lst)
		{
			last = *lst;
			while (last->next != NULL)
			{
				last = last->next;
			}
			last->next = new;
		}
		else
		{
			*lst = new;
		}
	}
}
