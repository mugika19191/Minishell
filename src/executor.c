/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:36:45 by enetxeba          #+#    #+#             */
/*   Updated: 2025/04/10 14:07:01 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(t_token *token, t_pipe *pipes)
{
	char	*com_w_path;

	if (token->command[0] == NULL)
		return ;
	if (built_in(token->command[0]))
	{
		exec_built_in(token, pipes, 1);
		return ;
	}
	com_w_path = joinpath(token, pipes);
	if (execve(com_w_path, token->command, *(pipes->env)) == -1
		&& !built_in(token->command[0]))
	{
		perror("command not found:");
		pipes->error_flag = set_flag(pipes, 127);
	}
	else
	{
		free(com_w_path);
		pipes->error_flag = set_flag(pipes, 0);
	}
}

void static	child(t_token *token, t_pipe *pipe_fd)
{
	redirec(token, pipe_fd);
	if (pipe_fd->prev_pipe[0] != -1)
	{
		if (dup2(pipe_fd->prev_pipe[0], STDIN_FILENO) == -1)
			exit(1);
		close(pipe_fd->prev_pipe[0]);
	}
	if (token->next != NULL)
	{
		if (dup2(pipe_fd->pipe_fd[1], STDOUT_FILENO) == -1)
			exit(1);
		close(pipe_fd->pipe_fd[1]);
	}
	execute(token, pipe_fd);
	exit(1);
}

void	dead_child(t_pipe *conf)
{
	pid_t	cpid;
	int		s_status;
	int		status;

	s_status = 0;
	cpid = 0;
	while (cpid != -1)
	{
		cpid = waitpid(-1, &conf->status, 0);
		if (cpid == conf->pid)
			s_status = conf->status;
		continue ;
	}
	if (WIFSIGNALED(s_status))
		status = 128 + WTERMSIG(s_status);
	else if (WIFEXITED(s_status))
		status = WEXITSTATUS(s_status);
	else
		conf->status = s_status;
	if (conf->error_flag != 130)
		set_flag(conf, s_status);
}

void	reset_pipes(t_pipe *pipes)
{
	pipes->prev_pipe[0] = -1;
	pipes->prev_pipe[1] = -1;
	set_flag(pipes, 0);
}

int	exe_token(t_token *token, t_pipe *pipes)
{
	if (built_in(token->command[0]) && !token->next
		&& token->redir_type == REDIR_NONE)
		return (exec_built_in(token, pipes, 0), 0);
	reset_pipes(pipes);
	while (token != NULL)
	{
		if (token->next || token->redir_type != REDIR_NONE)
		{
			if (pipe(pipes->pipe_fd) == -1)
				return (perror("error pipe"), set_flag(pipes, 1), 1);
		}
		if (token->redir_type == REDIR_HEREDOC)
			heredoc(token, pipes);
		pipes->pid = fork();
		if (pipes->pid < 0)
			return (perror("fork failed"), set_flag(pipes, 1), 1);
		if (pipes->pid == 0)
			child(token, pipes);
		else
			father(token, pipes);
		token = token->next;
	}
	dead_child(pipes);
	return (0);
}
