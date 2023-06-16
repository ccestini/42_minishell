/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:48:08 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/10 11:41:44 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand(char *str, char **envp);
int		ft_var_len(char *str, int i);
char	*ft_varname(char *str, int i);
char	*ft_dollar_exp_dq(char *var_value, char **envp);

char	*ft_expand(char *str, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (len != 0 && envp[i])
	{
		if (ft_strncmp(str, envp[i], len) == 0 && envp[i][len] == '=')
		{
			if (str)
				free(str);
			return (ft_strdup(&envp[i][len + 1]));
		}
		i++;
	}
	if (str)
		free(str);
	return (ft_strdup(""));
}

int	ft_var_len(char *str, int i)
{
	int	len;

	len = 0;
	if (ft_isdigit(str[i]))
		return (1);
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			len++;
		else
			return (len);
		i++;
	}
	return (len);
}

char	*ft_varname(char *str, int i)
{
	char	*var;
	int		len;

	len = ft_var_len(str, i);
	if (len == 0)
		return (NULL);
	var = ft_substr(str, i, len);
	return (var);
}

char	*ft_dollar_exp_dq(char *var_value, char **envp)
{
	int		j;
	char	*str;
	char	*expanded_str;

	j = 0;
	expanded_str = ft_strdup("");
	str = ft_strtrim(var_value, "\"");
	while (str[j])
	{
		if (str[j] == '$')
		{
			if (str[j] == '\'')
				expanded_str = ft_join_to_str(expanded_str, str[j]);
			else
				expanded_str = ft_get_dollar_val(str, &j, expanded_str, envp);
		}
		else
			expanded_str = ft_join_to_str(expanded_str, str[j]);
		j++;
	}
	expanded_str = ft_strjoin_m(ft_strdup("\""), expanded_str);
	expanded_str = ft_strjoin_m(expanded_str, ft_strdup("\""));
	free(str);
	return (expanded_str);
}
