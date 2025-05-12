/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endika <endika@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:19:31 by enetxeba          #+#    #+#             */
/*   Updated: 2025/01/15 17:02:59 by endika           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*ft_join(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

char	*ft_clean(char *buffer)
{
	int		c;
	int		i;
	char	*lin;

	c = 0;
	while (buffer[c] && buffer[c] != '\n')
		c++;
	if (!buffer[c])
	{
		free(buffer);
		return (NULL);
	}
	lin = ft_calloc((ft_strlen(buffer) - c + 1), sizeof(char));
	if (!lin)
		return (NULL);
	c++;
	i = 0;
	while (buffer[c])
		lin[i++] = buffer[c++];
	free(buffer);
	return (lin);
}

char	*ft_line(char *buffer)
{
	char	*lin;
	int		c;

	c = 0;
	if (!buffer[c])
		return (NULL);
	while (buffer[c] && buffer[c] != '\n')
		c++;
	lin = ft_calloc(c + 2, sizeof(char));
	if (!lin)
		return (NULL);
	c = 0;
	while (buffer[c] && buffer[c] != '\n')
	{
		lin[c] = buffer[c];
		c++;
	}
	if (buffer[c] && buffer[c] == '\n')
		lin[c++] = '\n';
	return (lin);
}

char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		bytes;

	if (!res)
		res = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes] = '\0';
		res = ft_join(res, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*lin;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	lin = ft_line(buffer);
	buffer = ft_clean(buffer);
	return (lin);
}
