/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:44:24 by enetxeba          #+#    #+#             */
/*   Updated: 2025/04/03 12:12:21 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	redirec(t_token *token, t_pipe *conf)
{
	if (token->redir_type == REDIR_IN)
		redir_in(token, conf);
	if (token->redir_type == REDIR_OUT || token->redir_type == REDIR_OUT_APPEND)
		redir_out(token, conf);
}

void	redir_in(t_token *token, t_pipe *conf)
{
	int	file;

	file = open(token->filename, O_RDONLY);
	if (file == -1)
	{
		perror("Error open");
		conf->error_flag = set_flag(conf, 1);
		exit(1);
	}
	if (dup2(file, STDIN_FILENO) == -1)
	{
		perror("Error dup2");
		conf->error_flag = set_flag(conf, 1);
		exit(1);
	}
	close(file);
}

void	redir_out(t_token *token, t_pipe *conf)
{
	int	file;

	if (token->redir_type == REDIR_OUT)
		file = open(token->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		file = open(token->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file == -1)
	{
		perror("Error open");
		conf->error_flag = set_flag(conf, 1);
		exit(1);
	}
	if (dup2(file, STDOUT_FILENO) == -1)
	{
		perror("Error dup2");
		conf->error_flag = set_flag(conf, 1);
		exit(1);
	}
	close(file);
}

void	redir_type(t_token *token, char **str, int *c)
{
	if (ft_strcmp(str[*c], ">"))
	{
		token->redir_type = REDIR_OUT;
		add_filename(token, str, c);
	}
	else if (ft_strcmp(str[*c], ">>"))
	{
		token->redir_type = REDIR_OUT_APPEND;
		add_filename(token, str, c);
	}
	else if (ft_strcmp(str[*c], "<"))
	{
		token->redir_type = REDIR_IN;
		add_filename(token, str, c);
	}
	else if (ft_strcmp(str[*c], "<<"))
	{
		token->redir_type = REDIR_HEREDOC;
		add_filename(token, str, c);
	}
}
