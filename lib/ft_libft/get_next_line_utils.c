/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:00:02 by enetxeba          #+#    #+#             */
/*   Updated: 2024/12/27 11:02:54 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*ret;
	size_t	c;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	ret = (char *) malloc (len_s1 + len_s2 + 1);
	if (ret == NULL)
		return (NULL);
	c = -1;
	while (++c < len_s1)
		ret[c] = s1[c];
	c = -1;
	while (++c < len_s2)
		ret[len_s1 + c] = s2[c];
	ret[len_s1 + c] = '\0';
	return (ret);
}

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (c & 0xFF))
			return ((char *) s);
		s++;
	}
	if ((c & 0xFF) == '\0')
		return ((char *) s);
	return (0);
}

size_t	ft_strlen(char *str)
{
	size_t	count;

	if (!str)
		return (0);
	count = 0;
	while (*str++ != '\0')
		count++;
	return (count);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc (nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero (ptr, nmemb * size);
	return (ptr);
}
