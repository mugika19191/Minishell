/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:50:44 by enetxeba          #+#    #+#             */
/*   Updated: 2025/04/10 12:12:29 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	*find_var(char *var, char **env)
{
	int		i;
	char	*str;

	i = -1;
	while (++i < env_len(env))
	{
		str = (char *)ft_strnstr(env[i], var, ft_strlen(var));
		if (str)
		{
			if (*(str + ft_strlen(var)) == '=')
			{
				return (str + ft_strlen(var) + 1);
			}
		}
	}
	return (NULL);
}

int	is_valid_env_var(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	if (str[i] != '=')
		return (0);
	if (str[i + 1] == '\0')
		return (0);
	return (1);
}

char	**edit_env(t_pipe *pipes, char *str)
{
	int		i;
	char	**split;
	char	**copy;

	split = ft_split(str, '=');
	i = env_len(*(pipes->env));
	copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = -1;
	while ((*(pipes->env))[++i])
	{
		if (ft_strncmp((*(pipes->env))[i], split[0], ft_strlen(split[0])) == 0
			&& (*((*(pipes->env))[i] + ft_strlen(split[0])) == '='))
			copy[i] = ft_strdup(str);
		else
			copy[i] = ft_strdup((*(pipes->env))[i]);
	}
	copy[i] = NULL;
	clean_command(split);
	clean_command(*(pipes->env));
	return (set_flag(pipes, 0), copy);
}

char	*cd_change_directory(const char *target, char *old_pwd)
{
	char	*new_pwd;

	if (!getcwd(old_pwd, 1024))
	{
		perror("getcwd");
		return (NULL);
	}
	if (chdir(target) != 0)
	{
		perror("cd");
		return (NULL);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		perror("getcwd");
		return (NULL);
	}
	return (new_pwd);
}
