/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:43:57 by enetxeba          #+#    #+#             */
/*   Updated: 2025/04/10 11:09:38 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*build_new_string(char *final, char *replace, char *var,
		unsigned int total_size)
{
	char			*temp;
	unsigned int	len;

	len = var - final;
	temp = malloc(total_size);
	ft_strlcpy(temp, final, len + 1);
	ft_strlcat(temp, replace, total_size);
	ft_strlcat(temp, final + len + get_var_len(var), total_size);
	free(final);
	return (temp);
}

char	*ft_strdup_free(char *str)
{
	char	*str_copy;

	str_copy = ft_strdup(str);
	free(str);
	return (str_copy);
}

char	*replace_var(char *str, t_pipe *pipes)
{
	char			*replace;
	char			*final;
	char			*var;
	unsigned int	len;
	unsigned int	total_size;

	final = ft_strdup(str);
	var = get_next_dolar(final, final);
	while (var)
	{
		replace = get_var(var, pipes);
		len = var - final;
		total_size = len + ft_strlen(replace) + ft_strlen(final + len
				+ get_var_len(var)) + 1;
		final = ft_strdup_free(build_new_string(final, replace, var,
					total_size));
		var = get_next_dolar(final, final + len + ft_strlen(replace));
	}
	return (final);
}

void	read_line_body(char *promp, t_pipe *pipes, char *line)
{
	char	**split;
	t_token	*token;

	promp = replace_var(line, pipes);
	split = shell_split(promp, ' ');
	token = tokenizer(split);
	clean_quotes(token);
	if (token->command)
	{
		exe_token(token, pipes);
		clean_token(token);
	}
	free(line);
	free(promp);
	clean_command(split);
}

int	read_line(t_pipe *pipes)
{
	char	*line;
	char	*promp;

	promp = create_prompt("@minishell ~ %", *(pipes->env));
	line = readline(promp);
	free(promp);
	if (line == NULL)
	{
		ft_exit(pipes);
		return (pipes->prog_flow = 0, 1);
	}
	if (quote_check(line))
		return (printf("Quotes not closed! \n"), free(line), 1);
	add_history(line);
	if (*line != '\0' && spaces(line))
	{
		read_line_body(promp, pipes, line);
	}
	else
	{
		free(line);
	}
	return (0);
}
