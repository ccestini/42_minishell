/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 10:10:20 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/02 18:46:09 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int		ft_isspace(char ch);
int		ft_get_wordlen(char *str, int i, char *delimit);
char	*ft_get_next_word(char *str, int i, char *delimit);
char	*ft_strjoin_m(char *s1, char *s2);
int		ft_print_2darray(char **str);

int	ft_isspace(char ch)
{
	if (ch == ' ' || ch == '\f' || ch == '\n'
		|| ch == '\t' || ch == '\v')
		return (1);
	return (0);
}

int	ft_get_wordlen(char *str, int i, char *delimit)
{
	int	len;

	len = i;
	while (str[len] && !ft_is_delimiter(str[len], delimit))
		len++;
	return (len - i);
}

char	*ft_get_next_word(char *str, int i, char *delimit)
{
	int		len;
	char	*word;

	word = NULL;
	len = ft_get_wordlen(str, i, delimit);
	if (len)
		word = ft_substr(str, i, len);
	return (word);
}

char	*ft_strjoin_m(char *s1, char *s2)
{
	char	*string;
	int		j;
	int		i;

	j = 0;
	i = 0;
	string = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (string == NULL)
		return (NULL);
	if (s1)
		while (s1[i])
			string[j++] = s1[i++];
	i = 0;
	if (s2)
		while (s2[i])
			string[j++] = s2[i++];
	string[j] = '\0';
	if (s1 != NULL)
		free (s1);
	if (s2 != NULL)
		free(s2);
	return (string);
}

int	ft_print_2darray(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		ft_putstr_fd(str[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (i);
}
