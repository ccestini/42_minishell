/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:52:55 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/13 13:41:24 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	**ft_copy_env(char **envp);
char	*ft_getenv(char *variable);
char	*ft_get_var_name(char *str);
int		ft_is_var_env(char *arg);
int		ft_is_var_env_loop(int i, char *var_name, char *arg, int size);

char	**ft_copy_env(char **envp)
{
	char	**env;
	int		nbr_strs;

	nbr_strs = 0;
	if (!envp)
		return (NULL);
	while (envp[nbr_strs])
	{
		nbr_strs++;
	}
	env = ft_calloc(sizeof(char *), nbr_strs + 1);
	nbr_strs = 0;
	while (envp[nbr_strs])
	{
		env[nbr_strs] = ft_strdup(envp[nbr_strs]);
		nbr_strs++;
	}
	env[nbr_strs] = NULL;
	return (env);
}

char	*ft_getenv(char *variable)
{
	int		i;
	int		j;
	char	*curr_envp;
	char	*value;

	i = 0;
	j = 0;
	value = NULL;
	while (g_shell.env[j])
	{
		i = 0;
		curr_envp = g_shell.env[j];
		while (variable[i] && curr_envp[i] && (variable[i] == curr_envp[i]))
			i++;
		if (!variable[i] && (curr_envp[i] == '=' || curr_envp[i] == '\0'))
		{
			value = &(curr_envp[i + 1]);
			return (value);
		}
		j++;
	}
	return (ft_strdup(""));
}

char	*ft_get_var_name(char *str)
{
	char	*var_name;
	int		i;
	int		len;

	i = 0;
	var_name = NULL;
	if (str[0] == '=')
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		var_name = ft_strdup(str);
	else
	{
		len = i - 0;
		var_name = ft_calloc(sizeof(char), (len + 1));
		i = 0;
		while (i < len)
		{
			var_name[i] = str[i];
			i++;
		}
		var_name[i] = '\0';
	}
	return (var_name);
}

int	ft_is_var_env(char *arg)
{
	int		i;
	int		j;
	char	*var_name;
	int		size;

	i = -1;
	var_name = ft_get_var_name(arg);
	if (!var_name)
		return (-1);
	size = (int)ft_strlen(var_name);
	j = ft_is_var_env_loop(i, var_name, arg, size);
	return (j);
}

int	ft_is_var_env_loop(int i, char *var_name, char *arg, int size)
{
	while (g_shell.env[++i])
	{
		if ((ft_strncmp(g_shell.env[i], var_name, size) == 0) && \
		(arg[size] == '=' && arg[size - 1] != 0) && g_shell.env[i][size] == '=')
		{
			free(g_shell.env[i]);
			g_shell.env[i] = ft_strdup(arg);
			free(var_name);
			return (-2);
		}
		else if ((ft_strncmp(g_shell.env[i], var_name, size) == 0) && \
				((arg[size] == '\0')))
		{
			free(var_name);
			return (0);
		}
	}
	free(var_name);
	return (-1);
}
