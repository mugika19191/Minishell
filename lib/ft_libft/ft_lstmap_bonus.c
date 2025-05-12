/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endika <endika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:44:43 by endika            #+#    #+#             */
/*   Updated: 2024/12/01 19:01:08 by endika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node_head;
	t_list	*new_node;
	t_list	*last_node;

	while (lst)
	{
		new_node = ft_lstnew(f (lst->content));
		if (!new_node)
		{
			ft_lstclear(&new_node_head, del);
			return (NULL);
		}
		if (!new_node_head)
		{
			new_node_head = new_node;
			last_node = new_node_head;
		}
		else
		{
			last_node->next = new_node;
			last_node = new_node;
		}
		lst = lst->next;
	}
	return (new_node_head);
}
