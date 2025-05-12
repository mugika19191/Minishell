/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:05:42 by enetxeba          #+#    #+#             */
/*   Updated: 2025/04/07 13:59:24 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	write_heredoc(t_pipe *pipe_fd, t_token *token, char *content)
{
	write(pipe_fd->pipe_fd[1], content, ft_strlen(content));
	close(pipe_fd->pipe_fd[1]);
	free(content);
	if (!token->next)
		pipe_fd->prev_pipe[0] = pipe_fd->pipe_fd[0];
}

char	*join_free(char *content, char *line)
{
	char	*free_cont;

	free_cont = content;
	content = ft_strjoin(content, line);
	free(free_cont);
	return (content);
}

void	heredoc(t_token *token, t_pipe *pipe_fd)
{
	char	*line;
	char	*content;

	content = NULL;
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (ft_strcmp(line, token->filename) == 1)
		{
			free(line);
			break ;
		}
		if (content)
			content = join_free(content, line);
		else
			content = ft_strdup(line);
		content = join_free(content, "\n");
		free(line);
	}
	write_heredoc(pipe_fd, token, content);
}
