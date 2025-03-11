/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroullea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 06:56:16 by aroullea          #+#    #+#             */
/*   Updated: 2024/10/11 06:54:36 by aroullea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ls_new;

	ls_new = NULL;
	ls_new = (t_list *) malloc (sizeof(t_list));
	if (ls_new == NULL)
		return (NULL);
	ls_new->content = content;
	ls_new->next = NULL;
	return (ls_new);
}
