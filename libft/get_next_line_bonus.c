/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:49:15 by ccestini          #+#    #+#             */
/*   Updated: 2022/09/21 14:18:08 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd);
char	*ft_gnl_read_file(int fd, char *str);

char	*get_next_line(int fd)
{
	static char	*str[256];
	char		*line;

	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0)
		return (NULL);
	str[fd] = ft_gnl_read_file(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = ft_gnl_get_line(str[fd]);
	str[fd] = ft_gnl_get_remain(str[fd]);
	return (line);
}

char	*ft_gnl_read_file(int fd, char *str)
{
	int		i;
	char	*remain;
	char	*buffer;

	i = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(buffer);
			return (NULL);
		}
		remain = str;
		buffer[i] = '\0';
		str = ft_gnl_join(remain, buffer);
		if (ft_gnl_hasline(str) >= 1)
			break ;
	}
	free(buffer);
	return (str);
}
