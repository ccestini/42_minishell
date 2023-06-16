/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:25:25 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/13 16:41:04 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*ft_join_to_str(char *str, char ch);
char	*ft_dollar_expansion_x(char *full_str, char **envp);
char	*ft_get_dollar_variable(char *str, int i);
char	*ft_get_dollar_val(char *full_str, int *i, char *new_str, char **envp);

char	*ft_join_to_str(char *str, char ch)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = ft_strlen(str);
	new_str = ft_calloc((j + 2), sizeof(char));
	if (!new_str)
	{
		free (str);
		return (NULL);
	}
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i++] = ch;
	new_str[i] = '\0';
	if (str)
		free (str);
	return (new_str);
}

char	*ft_dollar_expansion_x(char *full_str, char **envp)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = ft_strdup("");
	while (full_str[i])
	{
		if (full_str[i] == '\"')
		{
			new_str = ft_str_in_dq(full_str, &i, new_str, envp);
			continue ;
		}
		if (full_str[i] == '\'')
		{
			new_str = ft_str_in_sq(full_str, &i, new_str);
			continue ;
		}
		else if (full_str[i] == '$')
			new_str = ft_get_dollar_val(full_str, &i, new_str, envp);
		else
			new_str = ft_join_to_str(new_str, full_str[i]);
		i++;
	}
	return (new_str);
}

char	*ft_get_dollar_variable(char *str, int i)
{
	int	len;

	len = 0;
	if (str[++i] == '\"')
		return (ft_strdup(""));
	if (ft_isdigit(str[i]))
		return (ft_substr(str, i, 1));
	while (ft_isalnum(str[i + len]) == 1 || str[i + len] == '_')
			len++;
	return (ft_substr(str, i, len));
}

char	*ft_get_dollar_val(char *full_str, int *i, char *new_str, char **envp)
{
	char	*var;	
	char	*var_value;

	var_value = NULL;
	if (full_str[*i + 1] == '?')
	{
		new_str = ft_strjoin_m(new_str, ft_itoa(g_shell.exit_status));
		*i += 1;
	}
	else if (ft_isspace(full_str[*i + 1]) == 1 || full_str[*i + 1] == '\0')
		new_str = ft_strjoin_m(new_str, ft_strdup("$"));
	else
	{
		var = ft_get_dollar_variable(full_str, *i);
		*i = *i + ft_strlen(var);
		if (var)
			var_value = ft_expand(var, envp);
		if (var_value)
			new_str = ft_strjoin_m(new_str, var_value);
	}
	return (new_str);
}
