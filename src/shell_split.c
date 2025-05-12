/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:16:25 by enetxeba          #+#    #+#             */
/*   Updated: 2025/04/07 10:22:32 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	word_count(char const *str, char a)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (str[i])
	{
		if (str[i] != a && !in_word && !is_in_quotes(str, i))
		{
			in_word = 1;
			count++;
		}
		else if (str[i] == a && !is_in_quotes(str, i))
		{
			in_word = 0;
		}
		i++;
	}
	return (count);
}

static int	get_word_len(char const *str, char a, int pos)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	len = 0;
	while (str[i])
	{
		while (str[i] == a && str[i] && !is_in_quotes(str, i))
			i++;
		if (!str[i] && !count)
			return (0);
		while ((str[i] != a || is_in_quotes(str, i)) && str[i])
		{
			if (count == pos)
				len++;
			i++;
		}
		count++;
	}
	return (len);
}

static char	*get_word(char *word, const char *s, char c, int *k)
{
	int	i;

	i = 0;
	while (s[*k] == c && s[*k] && !is_in_quotes(s, *k))
		(*k)++;
	while ((s[*k] != c && s[*k] != '\0') || is_in_quotes(s, *k))
	{
		word[i++] = s[(*k)++];
	}
	word[i] = '\0';
	return (word);
}

static void	free_all(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
}

char	**shell_split(char const *s, char c)
{
	char	**str;
	int		i;
	int		k;

	if (!s)
		return (NULL);
	str = malloc(sizeof(char *) * (word_count((char *)s, c) + 1));
	if (!str)
		return (NULL);
	i = 0;
	k = 0;
	while (i < word_count((char *)s, c))
	{
		str[i] = malloc(get_word_len(s, c, i) + 1);
		if (!str[i])
		{
			free_all(str, i - 1);
			return (NULL);
		}
		str[i] = get_word(str[i], s, c, &k);
		i++;
	}
	str[i] = NULL;
	return (str);
}
