/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:14:19 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/09 12:41:20 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int		ft_2d_array_len(char **str);
int		ft_atoi_exit(char *str);
int		ft_check_open_q(char *str);
int		ft_is_directory(char *path);
int		ft_count_strs(char **str);

int	ft_2d_array_len(char **str)
{
	int	i;

	i = -1;
	if (str)
	{
		i = 0;
		while (str[i])
			i++;
	}
	return (i);
}

int	ft_atoi_exit(char *str)
{
	unsigned long	c;
	unsigned long	r;
	long			s;

	c = 0;
	r = 0;
	s = 1;
	while ((str[c] == ' ') || (str[c] == '\t') || (str[c] == '\r')
		|| (str[c] == '\n') || (str[c] == '\v') || (str[c] == '\f'))
		c++;
	if ((str[c] == '-') || (str[c] == '+'))
	{
		if (str[c++] == '-')
			s *= -1;
	}
	while ((str[c] >= '0') && (str[c] <= '9'))
		r = (str[c++] - '0') + (r * 10);
	if ((r > 2147483648 && s == -1) || (r > 2147483647 && s == 1))
	{
		ft_putstr_fd("my@shell: exit: numeric argument required\n", \
						STDERR_FILENO);
		return (255);
	}
	return (r * s);
}

int	ft_check_open_q(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i = ft_find_closed_quote(str, i);
			if (i == -1)
				return (-2);
		}
		i++;
	}
	return (0);
}

int	ft_is_directory(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (1);
	return (0);
}

int	ft_count_strs(char **str)
{
	int	i;
	int	len;
	int	count;

	i = -1;
	count = 0;
	len = 0;
	while (str[++i])
		len++;
	i = -1;
	while (i < len && str[++i])
	{
		if (str[i][0] == '\0')
			i++;
		else if ((ft_strcmp(str[i], "<") == 0 || ft_strcmp(str[i], ">") == 0 \
		|| ft_strcmp(str[i], "<<") == 0 || ft_strcmp(str[i], ">>") == 0))
			i ++;
		else
			count++;
	}
	return (count);
}
