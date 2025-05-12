/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:35:02 by enetxeba          #+#    #+#             */
/*   Updated: 2025/04/10 14:06:14 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*joinpath(t_token *token, t_pipe *conf)
{
	char	*path;

	if (!access(token->command[0], X_OK))
		return (token->command[0]);
	path = search_command(token->command[0], conf);
	if (path)
	{
		return (path);
	}
	return (NULL);
}

char	*search_command(char *comand, t_pipe *conf)
{
	char	*str;
	char	**str2;
	char	*path;
	int		j;
	char	*path2;

	j = 0;
	str = find_var ("PATH", *conf->env);
	if (str)
	{
		str2 = ft_split(str, ':');
		while (str2[j])
		{
			path2 = ft_strjoin(str2[j++], "/");
			path = ft_strjoin(path2, comand);
			free(path2);
			if (!access(path, X_OK))
				return (clean_command(str2), path);
			free(path);
		}
		clean_command(str2);
	}
	return ("");
}

void	father(t_token *token, t_pipe *pipe_fd)
{
	if (pipe_fd->prev_pipe[0] != -1)
		close(pipe_fd->prev_pipe[0]);
	if (token->next)
	{
		close(pipe_fd->pipe_fd[1]);
		pipe_fd->prev_pipe[0] = pipe_fd->pipe_fd[0];
	}
}
