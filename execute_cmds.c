/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:37:29 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/13 18:39:42 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int		ft_execute_cmds(t_cmd *cmd, int nbr_pipes, int fds[]);
int		ft_do_builtin_parent(t_cmd *cmd);
int		ft_dup_for_pipes(t_cmd *cmd, int fds[], int j);
int		ft_exe_child_afterdup(t_cmd *cmd, int nbr_pipes, int fds[], int pid[]);

int	ft_execute_cmds(t_cmd *cmd, int nbr_pipes, int fds[])
{
	int		*pid;
	int		j;
	int		i;

	j = 0;
	i = 0;
	if (ft_check_is_builtin_parent(cmd) == 1 && (nbr_pipes + 1) == 1)
		return (ft_do_builtin_parent(cmd));
	pid = ft_calloc(sizeof(int), nbr_pipes + 1);
	ft_open_pipes(nbr_pipes, fds);
	while (cmd)
	{
		pid[i] = fork();
		ft_check_fork_error(pid[i]);
		if (pid[i] == 0)
		{
			ft_dup_for_pipes(cmd, fds, j);
			ft_exe_child_afterdup(cmd, nbr_pipes, fds, pid);
		}
		cmd = cmd->next;
		j = j + 2;
		i++;
	}
	ft_close_wait_free(pid, nbr_pipes, fds);
	return (0);
}

int	ft_do_builtin_parent(t_cmd *cmd)
{
	ft_get_args_m(cmd->args, cmd);
	ft_fill_path_cmds(&cmd);
	ft_check_redirections_parent(cmd);
	ft_builtin_parent_exe(cmd, 0, 0);
	return (0);
}

int	ft_dup_for_pipes(t_cmd *cmd, int fds[], int j)
{
	if (cmd->next != NULL)
		dup2(fds[j + 1], STDOUT_FILENO);
	if (j != 0)
		dup2(fds[j - 2], STDIN_FILENO);
	return (0);
}

int	ft_exe_child_afterdup(t_cmd *cmd, int nbr_pipes, int fds[], int pid[])
{
	ft_close_pipes(fds, nbr_pipes);
	ft_get_args_m(cmd->args, cmd);
	ft_fill_path_cmds(&cmd);
	ft_check_redirection_input(cmd);
	ft_check_redirection_output(cmd);
	if (ft_check_is_builtin_parent(cmd) == 1)
	{
		ft_builtin_parent_exe(cmd, fds, pid);
		ft_clean_child(cmd, nbr_pipes, fds, pid);
		exit (EXIT_SUCCESS);
	}
	if (cmd->input_fd == -1)
	{
		ft_clean_child(cmd, nbr_pipes, fds, pid);
		exit (EXIT_FAILURE);
	}
	ft_check_is_builtin_child(&cmd, fds, pid);
	if (cmd->cmd_path != NULL)
		execve(cmd->cmd_path, cmd->args, g_shell.env);
	ft_clean_child_after_exe(cmd, nbr_pipes, fds, pid);
	exit(g_shell.exit_status);
	return (-1);
}
