/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:02:42 by mkovoor           #+#    #+#             */
/*   Updated: 2023/02/09 13:48:02 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int		ft_count_tokens(char *str, char *delimit);
int		ft_next_token_len(char *str, char *delimit, int start);
char	**ft_tokenize(char *str, char *delimit);
int		ft_is_delimiter(char ch, char *delimit);

int	ft_count_tokens(char *str, char *delimit)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_is_quote(str[i]))
			i = ft_find_closed_quote(str, i);
		if (ft_is_delimiter(str[i], delimit))
		{
			while (str[i] == str[i + 1])
				i++;
			count++;
		}
		else if (!ft_isspace(str[i]) && (str[i + 1] == '\0' || \
		ft_isspace(str[i + 1]) || ft_is_delimiter(str[i + 1], delimit)))
			count++;
		i++;
	}
	return (count);
}

int	ft_next_token_len(char *str, char *delimit, int start)
{
	int	i;

	i = start;
	while (str[i])
	{
		if (ft_is_quote(str[i]))
			i = ft_find_closed_quote(str, i);
		if (ft_is_delimiter(str[i], delimit))
		{
			while (str[i] == str[i + 1])
				i++;
			return (i - start + 1);
		}
		else if (!ft_isspace(str[i]) && (str[i + 1] == '\0' || \
		ft_isspace(str[i + 1]) || ft_is_delimiter(str[i + 1], delimit)))
			return (i - start + 1);
		i++;
	}
	return (-1);
}

char	**ft_tokenize(char *str, char *delimit)
{
	int		start;
	int		len;
	int		i;
	int		j;
	char	**split_tokens;

	start = -1;
	j = 0;
	i = ft_count_tokens(str, delimit);
	split_tokens = ft_calloc(sizeof(char *), (i + 1));
	while (++start < (int)ft_strlen(str))
	{
		if (!ft_isspace(str[start]))
		{
			len = ft_next_token_len(str, delimit, start);
			if (len > 0)
			{
				split_tokens[j++] = ft_substr(str, start, len);
				start = start + len - 1;
			}
		}
	}
	split_tokens[j] = 0;
	return (split_tokens);
}

int	ft_is_delimiter(char ch, char *delimit)
{
	while (*delimit)
	{
		if (*delimit == ch)
			return (1);
		delimit++;
	}
	return (0);
}
