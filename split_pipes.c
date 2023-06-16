/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:11:31 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/09 13:58:07 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	**ft_split_pipes(char *s, char c);
void	ft_write_nodes(char *s, char **split, char c);
int		ft_count_nodes(char *s);
int		ft_find_closed_quote(char *s, int i);
int		ft_find_pipe(char *s, int i, int *count);

char	**ft_split_pipes(char *s, char c)
{
	char	**split;
	int		i;

	if (!s)
		return (0);
	i = ft_count_nodes(s);
	if (i == -1)
	{
		ft_putstr_fd("my@shell: open quotes not supported\n", STDERR_FILENO);
		g_shell.exit_status = 1;
		return (NULL);
	}
	split = ft_calloc(sizeof(char *), (i + 1));
	if (!split)
		return (0);
	else
		ft_write_nodes(s, split, c);
	return (split);
}

void	ft_write_nodes(char *s, char **split, char c)
{
	int	last;
	int	j;
	int	start;

	last = 0;
	j = 0;
	start = -1;
	while ((size_t)last <= ft_strlen(s))
	{
		if ((s[last] == '\"' || s[last] == '\'') && s[last] != '\0')
		{
			if (last == 0)
				start = last;
			last = ft_find_closed_quote(s, last);
		}
		if (s[last] != c && start < 0)
			start = last;
		else if ((s[last] == c || (size_t)last == ft_strlen(s)) && start >= 0)
		{
			split[j++] = ft_substr(s, start, (last - start));
			start = -1;
		}
		last++;
	}
	split[j] = 0;
}

int	ft_count_nodes(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	if ((!s) || (s[0] == '\0'))
		return (0);
	while (s[i] != '\0')
	{
		if ((s[i] == '\"' || s[i] == '\'') && s[i] != '\0')
		{
			i = ft_find_closed_quote(s, i);
			if (i == -1)
				return (-1);
			i++;
		}
		else if (s[i] != '\"' && s[i] != '\'')
		{
			i = ft_find_pipe(s, i, &count);
		}
	}
	return (count);
}

int	ft_find_closed_quote(char *s, int i)
{
	char	c;

	c = s[i];
	i++;
	while (s[i] != c && s[i] != '\0')
		i++;
	if (s[i] == '\0')
	{
		return (-1);
	}
	return (i);
}

int	ft_find_pipe(char *s, int i, int *count)
{
	if (s[i] != '\0' && s[i] == '|')
	{
		(*count)++;
		i++;
	}
	while (s[i] && s[i] != '|' && s[i] != '\'' && s[i] != '\"' )
			i++;
	return (i);
}
