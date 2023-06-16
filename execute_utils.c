/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:48:50 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/10 16:20:11 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int		ft_check_fork_error(int pid);
void	ft_write_pipe_error(void);
int		ft_wait(int pid[], int nbr_pipes);
void	ft_close_wait_free(int pid[], int nbr_pipes, int fds[]);
void	ft_close_std_fds_child(void);

int	ft_check_fork_error(int pid)
{
	if (pid == -1)
	{
		ft_putstr_fd("Error: Problem forking process\n", STDERR_FILENO);
		g_shell.exit_status = 126;
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	ft_write_pipe_error(void)
{
	ft_putstr_fd("Error: Pipe not opened\n", STDERR_FILENO);
	g_shell.exit_status = 126;
	exit(EXIT_FAILURE);
}

int	ft_wait(int pid[], int nbr_pipes)
{
	int	i;
	int	status;

	i = 0;
	while (i < (nbr_pipes + 1))
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
				g_shell.exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				g_shell.exit_status = 130;
			else if (WTERMSIG(status) == SIGQUIT)
				g_shell.exit_status = 131;
			usleep(100);
		}
		i++;
	}
	return (0);
}

void	ft_close_wait_free(int pid[], int nbr_pipes, int fds[])
{
	ft_close_pipes(fds, nbr_pipes);
	ft_wait(pid, nbr_pipes);
	if (fds)
		free(fds);
	if (pid)
		free(pid);
}

void	ft_close_std_fds_child(void)
{
	if (g_shell.saved_out)
		close (g_shell.saved_out);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}
