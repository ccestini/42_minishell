/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:44:30 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/13 18:34:17 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	ft_clean_child_builtin(t_cmd **cmd, int nbr_pipes, int fds[]);
void	ft_clean_child(t_cmd *cmd, int nbr_pipes, int fds[], int pid[]);
void	ft_clean_child_after_exe(t_cmd *cmd, int nbr_pipes, int fds[], \
								int pid[]);

void	ft_clean_child_builtin(t_cmd **cmd, int nbr_pipes, int fds[])
{
	(void)nbr_pipes;
	g_shell.exit_status = 0;
	cmd = &g_shell.cmds;
	if (cmd)
		ft_free_cmds(cmd);
	if (g_shell.env)
		ft_free_2d_array(g_shell.env);
	if (fds)
		free(fds);
	ft_close_std_fds_child();
}

void	ft_clean_child_after_exe(t_cmd *cmd, int nbr_pipes, int fds[], \
								int pid[])
{
	(void)nbr_pipes;
	if (cmd->cmd_path == NULL && cmd->output_filename == NULL)
	{
		ft_putstr_fd("my@shell: command not found\n", STDERR_FILENO);
		g_shell.exit_status = 127;
	}
	else if (cmd->cmd_path && cmd->args[0][0] != '\0')
	{
		ft_putstr_fd("my@shell: is a directory\n", STDERR_FILENO);
		g_shell.exit_status = 126;
	}
	cmd = g_shell.cmds;
	ft_free_cmds(&cmd);
	if (g_shell.env)
		ft_free_2d_array(g_shell.env);
	if (fds)
		free(fds);
	if (pid)
		free(pid);
	ft_close_std_fds_child();
}

void	ft_clean_child(t_cmd *cmd, int nbr_pipes, int fds[], int pid[])
{
	cmd = g_shell.cmds;
	ft_free_cmds(&cmd);
	if (nbr_pipes > 0)
		ft_close_pipes(fds, nbr_pipes);
	if (g_shell.env)
		ft_free_2d_array(g_shell.env);
	if (fds)
		free(fds);
	if (pid)
		free(pid);
	ft_close_std_fds_child();
}
