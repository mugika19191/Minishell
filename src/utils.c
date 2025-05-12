/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:49:08 by enetxeba          #+#    #+#             */
/*   Updated: 2025/04/03 10:34:43 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	c;
	int	len;

	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	len = ft_strlen(s1);
	c = -1;
	while (++c < len)
	{
		if (s1[c] != s2[c])
			return (0);
	}
	return (1);
}

int	ft_arraylen(char **str)
{
	int	len;

	len = 0;
	while (str[len] != NULL)
		len++;
	return (len);
}

t_token	*ms_lstlast(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_token	*ms_lstadd_back(t_token *lst, t_token *new)
{
	t_token	*last;

	if (lst == NULL)
	{
		lst = new;
		return (new);
	}
	last = ms_lstlast(lst);
	last->next = new;
	return (lst);
}

void	clean_command(char **str)
{
	int	c;

	c = 0;
	while (str[c])
	{
		free(str[c]);
		c++;
	}
	free(str);
}
