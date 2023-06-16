/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:43:29 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/13 16:01:48 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int		ft_check_is_builtin_parent(t_cmd *cmd);
int		ft_builtin_parent_exe(t_cmd *cmd, int fds[], int pid[]);
int		ft_builtin_exit(char **args, t_cmd **cmd, int fds[], int pid[]);
int		ft_check_redirections_parent(t_cmd *cmd);

int	ft_check_is_builtin_parent(t_cmd *cmd)
{
	if (cmd->args)
	{
		if (ft_strcmp(cmd->args[0], "exit") == 0)
			return (1);
		if (ft_strcmp(cmd->args[0], "cd") == 0)
			return (1);
		if (ft_strcmp(cmd->args[0], "export") == 0)
			return (1);
		if (ft_strcmp(cmd->args[0], "unset") == 0)
			return (1);
	}
	return (0);
}

int	ft_builtin_parent_exe(t_cmd *cmd, int fds[], int pid[])
{
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		g_shell.exit_status = ft_builtin_exit(cmd->args, &cmd, fds, pid);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		g_shell.exit_status = ft_builtin_cd(cmd);
	if (ft_strcmp(cmd->args[0], "export") == 0)
		g_shell.exit_status = ft_builtin_export(cmd);
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		g_shell.exit_status = ft_builtin_unset(cmd);
	if (g_shell.saved_out)
		close(g_shell.saved_out);
	return (0);
}

int	ft_builtin_exit(char **args, t_cmd **cmd, int fds[], int pid[])
{
	int	i;
	int	nbr_pipes;

	i = 0;
	nbr_pipes = ft_lstcmd_size(*cmd) - 1;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (args[1] && args[2])
	{
		ft_putstr_fd("my@shell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	else if (!args[1])
		i = g_shell.exit_status;
	else if (args[1] && (ft_is_valid_nbrs(args[1]) == 0))
		i = (unsigned char)ft_atoi_exit(args[1]);
	else
		i = 255;
	ft_clean_child_builtin(cmd, nbr_pipes, fds);
	if (pid)
		free (pid);
	g_shell.exit_status = i;
	exit (i);
}

int	ft_check_redirections_parent(t_cmd *cmd)
{
	g_shell.saved_out = dup(STDOUT_FILENO);
	if (cmd->input_fd != 0)
	{
		dup2(cmd->input_fd, STDIN_FILENO);
		close(cmd->input_fd);
	}
	if (cmd->output_fd != 0)
	{
		dup2(cmd->output_fd, STDOUT_FILENO);
		close(cmd->output_fd);
	}
	return (0);
}
