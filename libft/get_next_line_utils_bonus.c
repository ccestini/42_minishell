/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 19:18:41 by ccestini          #+#    #+#             */
/*   Updated: 2022/06/13 15:03:58 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_gnl_strlen(char *str);
int			ft_gnl_hasline(char *str);
char		*ft_gnl_join(char *remain, char *buffer);
char		*ft_gnl_get_line(char *str);
char		*ft_gnl_get_remain(char *str);

char	*ft_gnl_get_line(char *str)
{
	int		i;
	char	*line;

	if (!str || str[0] == '\0')
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		line = malloc(sizeof(char) * (i + 2));
	if (str[i] == '\0')
		line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
			line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_gnl_get_remain(char *str)
{
	int		i;
	int		j;
	char	*remain;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[j] != '\n' && str[j] != '\0')
		j++;
	if (str[j] == '\0' || (str[j] == '\n' && str[j + 1] == '\0'))
	{
		free(str);
		return (NULL);
	}
	remain = malloc(sizeof(char) * (ft_gnl_strlen(str) - j));
	if (!remain)
		return (NULL);
	j = j + 1;
	while (str[j] != '\0')
		remain[i++] = str[j++];
	remain[i] = '\0';
	free(str);
	return (remain);
}

int	ft_gnl_hasline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

size_t	ft_gnl_strlen(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_gnl_join(char *remain, char *buffer)
{
	char	*new_str;
	int		i;
	int		n;
	int		len;

	if (!remain)
	{
		remain = malloc(sizeof(char) * 1);
		remain[0] = '\0';
	}
	len = ft_gnl_strlen(remain) + ft_gnl_strlen(buffer);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str || !buffer)
		return (NULL);
	i = 0;
	n = 0;
	while (remain[i] != '\0')
		new_str[n++] = remain[i++];
	i = 0;
	while (buffer[i] != '\0')
		new_str[n++] = buffer[i++];
	new_str[n] = '\0';
	free(remain);
	return (new_str);
}
