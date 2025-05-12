/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:10:21 by enetxeba          #+#    #+#             */
/*   Updated: 2025/04/10 12:13:20 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit(t_pipe *conf)
{
	char	*str[2];

	conf->prog_flow = 0;
	write(1, "Exit\n", 4);
}

char	**unset(t_pipe *pipes, char *str)
{
	int		i;
	char	**copy;
	int		j;

	set_flag(pipes, 0);
	if (!find_var(str, *(pipes->env)))
		return (*(pipes->env));
	i = env_len(*(pipes->env));
	copy = (char **)malloc(sizeof(char *) * (i));
	i = 0;
	j = 0;
	while ((*(pipes->env))[i])
	{
		if (ft_strnstr((*(pipes->env))[i], str, ft_strlen(str)))
			i++;
		else
			copy[j++] = ft_strdup((*(pipes->env))[i++]);
	}
	copy[j] = NULL;
	clean_command(*(pipes->env));
	return (copy);
}
