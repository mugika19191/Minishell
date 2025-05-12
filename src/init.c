/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:08:47 by enetxeba          #+#    #+#             */
/*   Updated: 2025/04/10 11:02:26 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**init_env(char **env)
{
	int		i;
	char	**copy;

	i = env_len(env);
	copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = -1;
	while (env[++i])
		copy[i] = ft_strdup(env[i]);
	copy[env_len(env)] = NULL;
	return (copy);
}

void	init_pipes(t_pipe *fd_pipes, char ***env)
{
	fd_pipes->prev_pipe[0] = -1;
	fd_pipes->prev_pipe[1] = -1;
	fd_pipes->status = 0;
	fd_pipes->pid = -1;
	fd_pipes->prog_flow = 1;
	fd_pipes->pid_shell = getpid();
	(fd_pipes->env) = env;
	*(fd_pipes->env) = init_env(*env);
	fd_pipes->saved_stdout = dup(STDOUT_FILENO);
	fd_pipes->saved_stdin = dup(STDIN_FILENO);
	fd_pipes->error_flag = 0;
	fd_pipes->flag_str = ft_itoa(0);
}

int	get_var_len(char *str)
{
	int	i;

	i = 0;
	if (str[1] == '?' && !ft_isalnum(str[2]))
		return (2);
	while (ft_isalnum(str[++i]))
		;
	return (i);
}

char	*get_var(char *str, t_pipe *pipes)
{
	int		i;
	char	*var;
	char	*value;

	i = 1;
	if (str[i] == '?')
	{
		return (pipes->flag_str);
	}
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (i == 1)
		return ("$");
	var = malloc(i + 1);
	ft_strlcpy(var, str, i + 1);
	value = find_var(var + 1, *(pipes->env));
	free(var);
	if (value)
		return (value);
	return ("");
}

int	spaces(char *str)
{
	while (*str)
	{
		if (*(str++) != ' ')
			return (1);
	}
	return (0);
}
