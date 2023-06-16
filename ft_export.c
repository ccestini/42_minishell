/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:56:11 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/13 13:40:51 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int		ft_builtin_export(t_cmd *cmd);
char	**ft_insert_var_env(char *str, char **envp);
int		ft_valid_var_export(char *str);
char	**ft_sort_export_2darray(char **str);
void	ft_export_print(void);

int	ft_builtin_export(t_cmd *cmd)
{
	int	i;
	int	r;

	r = 0;
	if (!cmd->args[1])
		ft_export_print();
	else
	{
		i = 0;
		while (cmd->args[++i])
		{
			if (ft_is_var_env(cmd->args[i]) == -1)
			{
				if (ft_valid_var_export(cmd->args[i]) == 0)
					g_shell.env = ft_insert_var_env(cmd->args[i], g_shell.env);
				else
					r = 1;
			}
			else
				r = 1;
		}
	}
	return (r);
}

char	**ft_insert_var_env(char *str, char **envp)
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
	env = ft_calloc(sizeof(char *), nbr_strs + 2);
	nbr_strs = 0;
	while (envp[nbr_strs])
	{
		env[nbr_strs] = ft_strdup(envp[nbr_strs]);
		nbr_strs++;
	}
	env[nbr_strs++] = ft_strdup(str);
	env[nbr_strs] = 0;
	ft_free_2d_array(envp);
	return (env);
}

int	ft_valid_var_export(char *str)
{
	char	*var_name;
	int		i;

	if ((str[0] != '_') && (ft_isalpha(str[0]) == 0))
	{	
		ft_putstr_fd("my@shell: not a valid identifier\n", STDERR_FILENO);
		return (1);
	}
	var_name = ft_get_var_name(str);
	i = 1;
	while (var_name[i])
	{
		if (var_name[i] == '_' || ft_isalpha(var_name[i]) == 1 || \
			ft_isdigit(var_name[i]) == 1)
			i++;
		else
		{	
			ft_putstr_fd("my@shell: not a valid identifier\n", STDERR_FILENO);
			free(var_name);
			return (1);
		}
	}
	free(var_name);
	return (0);
}

char	**ft_sort_export_2darray(char **str)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[j])
		{
			if (ft_strcmp(str[i], str[j]) < 0)
			{
				temp = str[i];
				str[i] = str[j];
				str[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (str);
}

void	ft_export_print(void)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (g_shell.env == NULL)
		return ;
	ft_sort_export_2darray(g_shell.env);
	while (g_shell.env[i])
	{
		if (ft_strchr(g_shell.env[i], '='))
		{
			printf("declare -x ");
			while (g_shell.env[i][j] && g_shell.env[i][j] != '=')
				printf("%c", g_shell.env[i][j++]);
			printf("=\"%s\"\n", &g_shell.env[i][++j]);
		}
		else
			printf("declare -x %s\n", g_shell.env[i]);
		i++;
		j = 0;
	}
	dup2(g_shell.saved_out, STDOUT_FILENO);
}
