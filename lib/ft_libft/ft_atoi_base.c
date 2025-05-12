/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enetxeba <enetxeba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:13:27 by enetxeba          #+#    #+#             */
/*   Updated: 2025/04/10 12:18:39 by enetxeba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_find_char(char car, char *base)
{
	int	c;

	c = 0;
	while (base[c] != '\0')
	{
		if (car == base[c])
			return (c);
		c++;
	}
	return (0);
}

unsigned int	ft_atoi_base(char *str, char *base)
{
	int				c;
	unsigned int	num;
	int				baselen;
	int				basepos;

	num = 0;
	c = 0;
	baselen = ft_strlen(base);
	while (str[c] != '\0')
	{
		basepos = ft_find_char(str[c], base);
		num = num * baselen + basepos;
		c++;
	}
	if (num == 0)
		return (0);
	return (num);
}
