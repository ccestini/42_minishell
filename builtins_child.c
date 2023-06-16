/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:31:08 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/10 13:08:26 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int		ft_check_is_builtin_child(t_cmd **cmd, int fds[], int pid[]);
int		ft_builtin_pwd(t_cmd **cmd, int fds[], int pid[]);
int		ft_builtin_env(t_cmd **cmd, int fds[], int pid[]);

int	ft_check_is_builtin_child(t_cmd **cmd, int fds[], int pid[])
{
	if ((*cmd)->args)
	{
		if (ft_strcmp((*cmd)->args[0], "pwd") == 0)
			g_shell.exit_status = ft_builtin_pwd(cmd, fds, pid);
		else if (ft_strcmp((*cmd)->args[0], "echo") == 0)
			g_shell.exit_status = ft_builtin_echo(cmd, fds, pid);
		else if (ft_strcmp((*cmd)->args[0], "env") == 0)
			g_shell.exit_status = ft_builtin_env(cmd, fds, pid);
	}
	return (0);
}

int	ft_builtin_pwd(t_cmd **cmd, int fds[], int pid[])
{
	char	*pwd;
	int		nbr_pipes;	

	nbr_pipes = ft_lstcmd_size(*cmd);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_putstr_fd("my@shell: directory not found\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd(pwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	free(pwd);
	ft_clean_child_builtin(cmd, nbr_pipes, fds);
	free(pid);
	exit (g_shell.exit_status);
}

int	ft_builtin_env(t_cmd **cmd, int fds[], int pid[])
{
	int	i;
	int	nbr_pipes;	

	nbr_pipes = ft_lstcmd_size(*cmd);
	i = 0;
	if (g_shell.env == NULL)
		return (0);
	while (g_shell.env[i])
	{
		if (ft_strchr(g_shell.env[i], '='))
			printf("%s\n", g_shell.env[i]);
		i++;
	}
	ft_clean_child_builtin(cmd, nbr_pipes, fds);
	free(pid);
	exit (g_shell.exit_status);
}
