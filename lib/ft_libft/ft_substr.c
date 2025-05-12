/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:24:08 by enetxeba          #+#    #+#             */
/*   Updated: 2024/12/02 12:00:32 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	c;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	res = malloc (len + 1);
	if (res == NULL)
		return (NULL);
	c = 0;
	while (s[start + c] != '\0' && c < len)
	{
		res[c] = s[start + c];
		c++;
	}
	res[c] = '\0';
	return (res);
}
