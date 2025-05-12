/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:16:09 by enetxeba          #+#    #+#             */
/*   Updated: 2025/04/10 10:42:44 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	quote_comp(char c, char quote)
{
	if (c == ' ')
		return (0);
	if (c == quote)
		return (0);
	return (1);
}

int	is_in_quotes(char const *str, int pos)
{
	int		i;
	int		open;
	char	c;

	i = 0;
	open = 0;
	c = ' ';
	while (str[i] && i != pos)
	{
		if (str[i] == c && open)
		{
			open = !open;
			c = ' ';
		}
		else if (str[i] == '\'' || str[i] == '"')
		{
			if (!open)
			{
				c = str[i];
				open = !open;
			}
		}
		i++;
	}
	return (open * quote_comp(c, str[i]));
}

int	quote_check(char *str)
{
	int		i;
	int		open;
	char	quote_type;

	open = 0;
	quote_type = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (open == 0)
			{
				open = 1;
				quote_type = str[i];
			}
			else if (str[i] == quote_type)
			{
				open = 0;
				quote_type = 0;
			}
		}
		i++;
	}
	return (open);
}

char	*get_next_dolar(const char *string, char *var)
{
	char	quotes;
	int		open;

	quotes = ' ';
	open = 0;
	while (*string)
	{
		if ((*string == '\'' || *string == '\"'))
		{
			if (*string == quotes && open)
			{
				quotes = ' ';
				open = !open;
			}
			else if (!open)
			{
				quotes = *string;
				open = !open;
			}
		}
		if (*string == '$' && quotes != '\'' && (string - var) >= 0)
			return ((char *)string);
		string++;
	}
	return (0);
}
