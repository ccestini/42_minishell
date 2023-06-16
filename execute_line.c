/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:45:22 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/13 18:42:39 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int		ft_execute_line(t_cmd *cmd);
int		ft_check_redirection_input(t_cmd *cmd);
int		ft_check_redirection_output(t_cmd *cmd);
int		*ft_open_pipes(int nbr_pipes, int fds[]);
int		ft_close_pipes(int pipesfds[], int nbr_pipes);

int	ft_execute_line(t_cmd *cmd)
{
	int	nbr_cmds;
	int	nbr_pipes;
	int	*fds;

	nbr_cmds = ft_lstcmd_size(cmd);
	nbr_pipes = nbr_cmds - 1;
	fds = 0;
	if (nbr_pipes > 0)
		fds = ft_calloc(sizeof(int), (nbr_pipes * 2) + 1);
	ft_signals_received(2);
	ft_execute_cmds(cmd, nbr_pipes, fds);
	return (0);
}

int	ft_check_redirection_input(t_cmd *cmd)
{
	if (cmd->input_fd != 0)
	{
		dup2(cmd->input_fd, STDIN_FILENO);
		close(cmd->input_fd);
	}
	return (0);
}

int	ft_check_redirection_output(t_cmd *cmd)
{
	if (cmd->output_fd != 0)
	{
		dup2(cmd->output_fd, STDOUT_FILENO);
		close(cmd->output_fd);
	}
	return (0);
}

int	*ft_open_pipes(int nbr_pipes, int fds[])
{
	int	i;

	i = 0;
	while (i < nbr_pipes)
	{
		if (pipe(fds + (i * 2)) == -1)
			ft_write_pipe_error();
		i++;
	}
	return (fds);
}

int	ft_close_pipes(int fds[], int nbr_pipes)
{
	int	i;

	i = 0;
	if (nbr_pipes == 0)
		return (0);
	while (fds && (i < (nbr_pipes * 2)))
	{
		if (fds[i])
			close(fds[i]);
		i++;
	}
	if (g_shell.saved_out)
		close(g_shell.saved_out);
	return (0);
}
