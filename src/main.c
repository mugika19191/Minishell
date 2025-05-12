/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:14:45 by enetxeba          #+#    #+#             */
/*   Updated: 2025/04/10 12:07:31 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*g_env_pointer = NULL;

char	*create_prompt(char *str, char **env)
{
	char	*user;
	char	*path;
	char	*tmp;

	user = ft_strjoin(find_var("USER", env), "@minishell ~ %");
	path = ft_strtrim(find_var("PWD", env), find_var("HOME", env));
	tmp = ft_strjoin(user, path);
	free(user);
	free(path);
	path = ft_strjoin(tmp, "> ");
	free(tmp);
	return (path);
}

int	main(int count, char **args, char **env)
{
	char				*promp;
	struct sigaction	sig;
	t_pipe				pipes;

	init_pipes(&pipes, &env);
	if (init_sigaction(&sig, &pipes))
		return (perror("error sigaction"), -1);
	g_env_pointer = &pipes;
	while (pipes.prog_flow)
	{
		read_line(&pipes);
	}
	clean_command(*pipes.env);
	free(pipes.flag_str);
	rl_clear_history();
	return (0);
}
