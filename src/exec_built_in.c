/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:59:00 by enetxeba          #+#    #+#             */
/*   Updated: 2025/04/10 12:14:41 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	built_in(char *str)
{
	return (ft_strcmp(str, "cd") || ft_strcmp(str, "export") || ft_strcmp(str,
			"pwd") || ft_strcmp(str, "env") || ft_strcmp(str, "echo")
		|| ft_strcmp(str, "exit") || ft_strcmp(str, "unset"));
}

void	exec_built_in(t_token *token, t_pipe *conf, int mode)
{
	int	i;

	i = 1;
	if (ft_strcmp(token->command[0], "cd"))
		cd(token, conf);
	else if (ft_strcmp(token->command[0], "export"))
	{
		while (token->command[i])
			*(conf->env) = export(conf, token->command[i++]);
	}
	else if (ft_strcmp(token->command[0], "pwd"))
		pwd(conf);
	else if (ft_strcmp(token->command[0], "env"))
		env(token, conf);
	else if (ft_strcmp(token->command[0], "echo"))
		echo(token, conf);
	else if (ft_strcmp(token->command[0], "exit"))
		ft_exit(conf);
	else if (ft_strcmp(token->command[0], "unset"))
	{
		while (token->command[i])
			*(conf->env) = unset(conf, token->command[i++]);
	}
	if (mode)
		exit(conf->error_flag);
}
