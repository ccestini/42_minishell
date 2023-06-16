/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 07:35:12 by mkovoor           #+#    #+#             */
/*   Updated: 2023/02/13 16:41:58 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int		ft_is_quote(char ch);
char	*ft_str_in_sq(char *full_str, int *i, char *new_str);
char	*ft_str_in_dq(char *full_str, int *i, char *new_str, char **envp);
char	*ft_check_for_quotes(char *str);
int		ft_is_valid_nbrs(char *nbrs);

int	ft_is_quote(char ch)
{
	if (ch == '\"' || ch == '\'')
		return (1);
	return (0);
}

char	*ft_str_in_sq(char *full_str, int *i, char *new_str)
{
	char	*var_value;
	int		len;

	var_value = NULL;
	len = ft_find_closed_quote(full_str, *i) - *i + 1;
	var_value = ft_substr(full_str, *i, len);
	*i = *i + len;
	var_value = ft_strjoin_m(new_str, var_value);
	return (var_value);
}

char	*ft_str_in_dq(char *full_str, int *i, char *new_str, char **envp)
{
	char	*var_value;
	char	*expanded_str;
	int		len;

	var_value = NULL;
	len = ft_find_closed_quote(full_str, *i) - *i + 1;
	var_value = ft_substr(full_str, *i, len);
	expanded_str = ft_dollar_exp_dq(var_value, envp);
	free(var_value);
	var_value = ft_strjoin_m(new_str, expanded_str);
	*i = *i + len;
	return (var_value);
}

char	*ft_check_for_quotes(char *str)
{
	int		i;
	int		start;
	char	*new_str;

	i = -1;
	new_str = ft_strdup("");
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			start = i + 1;
			i = ft_find_closed_quote(str, i);
			new_str = ft_strjoin_m(new_str, ft_substr(str, start, i - start));
		}
		else
			new_str = ft_join_to_str(new_str, str[i]);
	}
	return (new_str);
}

int	ft_is_valid_nbrs(char *nbrs)
{
	int	i;

	i = 0;
	while (nbrs[i])
	{
		if (ft_isdigit(nbrs[i]) == 0 && nbrs[i] != '+' && nbrs[i] != '-')
		{
			ft_putstr_fd("my@shell: exit: numeric argument required\n", \
						STDERR_FILENO);
			return (255);
		}	
		i++;
	}
	return (0);
}
