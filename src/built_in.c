/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:15:19 by enetxeba          #+#    #+#             */
/*   Updated: 2025/04/10 12:16:14 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pwd(t_pipe *conf)
{
	set_flag(conf, 0);
	printf("%s\n", find_var("PWD", *(conf->env)));
}

void	env(t_token *token, t_pipe *conf)
{
	int	i;

	i = 0;
	if (token->command[1])
	{
		printf("env: ‘%s’: No such file or directory\n", token->command[1]);
		set_flag(conf, 127);
		return ;
	}
	while ((*(conf->env))[i])
		printf("%s\n", (*(conf->env))[i++]);
	set_flag(conf, 0);
}

char	**export(t_pipe *pipes, char *str)
{
	int		i;
	char	**copy;
	char	**split;

	set_flag(pipes, 0);
	if (!is_valid_env_var(str))
		return (printf ("export: `%s': not a valid identifier\n", str),
			set_flag(pipes, 1), *(pipes->env));
	split = ft_split(str, '=');
	if (!find_var(split[0], *(pipes->env)))
	{
		i = env_len(*(pipes->env));
		copy = (char **)malloc(sizeof(char *) * (i + 2));
		i = -1;
		while ((*(pipes->env))[++i])
			copy[i] = ft_strdup((*(pipes->env))[i]);
		copy[env_len(*(pipes->env))] = ft_strdup(str);
		copy[env_len(*(pipes->env)) + 1] = NULL;
	}
	else
	{
		clean_command(split);
		return (edit_env(pipes, str));
	}
	return (clean_command(*(pipes->env)), clean_command(split), copy);
}

void	echo(t_token *token, t_pipe *conf)
{
	int	i;
	int	mode;

	i = 1;
	mode = 1;
	if (ft_strcmp(token->command[i], "-n"))
	{
		i++;
		mode = 0;
	}
	while (token->command[i])
	{
		write(1, token->command[i], ft_strlen(token->command[i]));
		if (token->command[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (mode)
		write(1, "\n", 1);
	set_flag(conf, 0);
}

int	cd(t_token *token, t_pipe *pipes)
{
	char	old_pwd[1024];
	char	*new_pwd;
	char	*target;
	char	*join;

	target = token->command[1];
	if (!target)
	{
		target = find_var("HOME", *(pipes->env));
		if (!target)
			return (set_flag(pipes, 1), printf("cd: HOME not set\n"), 1);
	}
	new_pwd = cd_change_directory(target, old_pwd);
	if (!new_pwd)
		return (set_flag(pipes, 1), 1);
	join = ft_strjoin("OLDPWD=", old_pwd);
	*(pipes->env) = edit_env(pipes, join);
	free(join);
	join = ft_strjoin("PWD=", new_pwd);
	*(pipes->env) = edit_env(pipes, join);
	free(new_pwd);
	free(join);
	set_flag(pipes, 0);
	return (0);
}
