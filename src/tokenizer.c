/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:18:40 by enetxeba          #+#    #+#             */
/*   Updated: 2025/04/07 13:59:47 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*tokenizer(char **str)
{
	t_token	*token;
	int		len;
	int		c;

	token = NULL;
	len = ft_arraylen(str);
	c = 0;
	while (str[c] != NULL)
	{
		if (!is_connector(str[c]))
			token = ms_lstadd_back(token, new_token(str, &c));
		if (str[c] != NULL)
			c++;
	}
	return (token);
}

void	link_type(t_token *token, char **str, int *c)
{
	if (ft_strcmp(str[*c], "|"))
		token->type = TOKEN_PIPE;
	else if (ft_strcmp(str[*c], "&&"))
		token->type = TOKEN_AND;
	else if (ft_strcmp(str[*c], "||"))
		token->type = TOKEN_OR;
	else
		token->type = TOKEN_EOF;
}

t_token	*reserve_mem(char **str, int **c)
{
	t_token	*token;
	int		len;
	int		i;

	token = malloc(sizeof(t_token));
	token->next = NULL;
	if (token == NULL)
		return (NULL);
	len = 0;
	while (!is_connector(str[**c + len]) && str[**c + len] != NULL)
		len++;
	token->command = malloc (sizeof(char *) * (len + 1));
	i = 0;
	while (i < len)
	{
		token->command[i] = NULL;
		i++;
	}
	if (!token->command)
		return (perror ("malloc error"), NULL);
	token->command[len] = NULL;
	return (token);
}

void	heredoc_token(t_token *token, char **str, int **c)
{
	token->command[0] = strdup("cat");
	token->type = 0;
	token->redir_type = REDIR_HEREDOC;
	(**c)++;
	token->filename = ft_strdup(str[**c]);
	(**c)++;
}

t_token	*new_token(char **str, int *c)
{
	t_token	*token;
	char	*args;
	int		len;

	token = reserve_mem(str, &c);
	if (token == NULL)
		return (NULL);
	len = 0;
	if (ft_strcmp(str[*c], "<<"))
		return (heredoc_token (token, str, &c), token);
	token->filename = NULL;
	while (!is_connector(str[*c]) && str[*c] != NULL)
	{
		if (!is_in_out(str[*c]))
		{
			token->redir_type = REDIR_NONE;
			token->command[len] = ft_strdup(str[*c]);
		}
		else
			redir_type(token, str, c);
		(*c)++;
		len ++;
	}
	link_type(token, str, c);
	return (token);
}
