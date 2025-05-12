/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:56:04 by enetxeba          #+#    #+#             */
/*   Updated: 2025/04/07 13:54:38 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_connector(char *str)
{
	return (ft_strcmp(str, "|") || ft_strcmp(str, "&") || ft_strcmp(str, "|"));
}

int	is_in_out(char *str)
{
	return (ft_strcmp(str, "<") || ft_strcmp(str, ">") || ft_strcmp(str, ">>")
		|| ft_strcmp(str, "<<"));
}

void	add_filename(t_token *token, char **str, int *c)
{
	(*c)++;
	token->filename = ft_strdup(str[*c]);
}

int	pt_lstsize(t_token *lst)
{
	int	cnt;

	cnt = 0;
	while (lst)
	{
		lst = lst->next;
		cnt++;
	}
	return (cnt);
}

void	clean_token(t_token *token)
{
	t_token	*tmp;
	int		c;

	c = pt_lstsize(token);
	while (c > 0)
	{
		if (token->command != NULL)
		{
			if (token->filename != NULL)
				free(token->filename);
			clean_command(token->command);
			token->command = NULL;
		}
		tmp = token->next;
		free(token);
		token = tmp;
		c--;
	}
}
