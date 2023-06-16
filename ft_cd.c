/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:54:29 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/13 19:25:00 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int		ft_builtin_cd(t_cmd *cmd);
int		ft_cd_go(char **args);
int		ft_cd_only(char **args);
int		ft_update_pwd(char *pwd);

int	ft_builtin_cd(t_cmd *cmd)
{
	int		nbr_args;
	char	*pwd;

	nbr_args = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	while (cmd->args[nbr_args])
		nbr_args++;
	if (nbr_args == 1)
	{	
		if (ft_cd_only(cmd->args) == 1)
			return (1);
	}
	else if (nbr_args >= 2)
	{
		if (ft_cd_go(cmd->args) == 1)
			return (1);
	}
	ft_update_pwd(pwd);
	if (pwd)
		free(pwd);
	if (g_shell.saved_out)
		close (g_shell.saved_out);
	return (0);
}

int	ft_cd_only(char **args)
{
	(void)args;
	if ((chdir(ft_getenv("HOME")) == -1))
	{	
		ft_putstr_fd("my@shell: cd: HOME not set\n", 2);
		return (1);
	}
	return (0);
}

int	ft_cd_go(char **args)
{
	if (ft_strcmp(args[1], "~") == 0)
	{
		if ((chdir(ft_getenv("HOME")) == -1))
		{
			ft_putstr_fd("my@shell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if ((chdir(ft_getenv("OLDPWD")) == -1))
		{
			ft_putstr_fd("my@shell: cd: OLDPWD not set\n", 2);
			return (1);
		}
	}
	else
	{
		if (chdir(args[1]) == -1)
		{
			ft_putstr_fd("my@shell: cd: No such file or directory\n", 2);
			return (1);
		}
	}
	return (0);
}

int	ft_update_pwd(char *pwd)
{
	char	*str_old;
	char	*str_new;
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (1);
	str_old = ft_strjoin("OLDPWD=", pwd);
	str_new = ft_strjoin("PWD=", new_pwd);
	free(new_pwd);
	if (ft_is_var_env(str_old) == -1)
		g_shell.env = ft_insert_var_env(str_old, g_shell.env);
	ft_is_var_env(str_new);
	free(str_old);
	free(str_new);
	return (0);
}
