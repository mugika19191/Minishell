/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endika <endika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:46:44 by enetxeba          #+#    #+#             */
/*   Updated: 2024/11/29 12:02:19 by endika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*ret;
	size_t	c;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	ret = (char *) malloc (len_s1 + len_s2 + 1);
	if (ret == NULL)
		return (NULL);
	c = 0;
	while (c < len_s1)
	{
		ret[c] = s1[c];
		c++;
	}
	c = 0;
	while (c < len_s2)
	{
		ret[len_s1 + c] = s2[c];
		c++;
	}
	ret[len_s1 + c] = '\0';
	return (ret);
}
