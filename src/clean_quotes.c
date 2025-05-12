/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:11:43 by enetxeba          #+#    #+#             */
/*   Updated: 2025/04/10 10:46:11 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*remove_quotes(char *s)
{
	int		i;
	int		j;
	char	*str2;
	char	open;

	i = -1;
	j = 0;
	open = ' ';
	str2 = (char *)malloc(strlen(s) + 1);
	if (str2 == NULL)
		return (NULL);
	while (s[++i])
	{
		if ((s[i] == '"' || s[i] == '\'') && (open == ' ' || open == s[i]))
		{
			if (open == ' ')
				open = s[i];
			else if (open == s[i])
				open = ' ';
		}
		else
			str2[j++] = s[i];
	}
	str2[j] = '\0';
	return (free(s), str2);
}

void	clean_quotes(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		while (token->command[i])
		{
			token->command[i] = remove_quotes(token->command[i]);
			i++;
		}
		i = 0;
		token = token->next;
	}
}

int	set_flag(t_pipe *pipes, int error)
{
	free(pipes->flag_str);
	pipes->flag_str = ft_itoa(error);
	pipes->error_flag = error;
	return (error);
}
