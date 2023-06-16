/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:59:38 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/13 14:02:14 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int		ft_builtin_unset(t_cmd *cmd);
char	**ft_delete_var_env(char **envp, int i);
int		ft_check_env_unset(char *arg);

int	ft_builtin_unset(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (cmd->args[i])
	{
		if (ft_valid_var_export(cmd->args[i]) != 0)
		{
			i++;
			continue ;
		}
		j = ft_check_env_unset(cmd->args[i]);
		if (j >= 0)
			g_shell.env = ft_delete_var_env(g_shell.env, j);
		i++;
	}
	if (g_shell.saved_out)
		close (g_shell.saved_out);
	return (0);
}

char	**ft_delete_var_env(char **envp, int i)
{
	char	**env;
	int		nbr_strs;
	int		nbr_new_strs;

	nbr_strs = 0;
	nbr_new_strs = 0;
	if (!envp)
		return (NULL);
	while (envp[nbr_strs])
		nbr_strs++;
	env = ft_calloc(sizeof(char *), nbr_strs);
	nbr_strs = 0;
	while (envp[nbr_strs])
	{
		if (nbr_strs != i)
			env[nbr_new_strs++] = ft_strdup(envp[nbr_strs++]);
		else
			nbr_strs++;
	}
	env[nbr_new_strs] = 0;
	ft_free_2d_array(envp);
	return (env);
}

int	ft_check_env_unset(char *arg)
{
	int		i;
	char	*var_name;
	size_t	size;

	i = -1;
	var_name = arg;
	size = ft_strlen(var_name);
	while (g_shell.env[++i])
	{
		if ((ft_strncmp(g_shell.env[i], var_name, size) == 0) && \
		(g_shell.env[i][size] == '=' || g_shell.env[i][size] == '\0'))
		{
			return (i);
		}
	}
	return (-1);
}
