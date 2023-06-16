/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:12:56 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/10 18:09:20 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signals_received(int where);
void	ft_restore_prompt(int sig);
void	ft_ctrl_c(int sig);
void	ft_backslash(int sig);
void	ft_received_ctrl_d(t_cmd **cmd);

// 0 is to ignore, 1 for parent, 2 for child, 3 for hd
void	ft_signals_received(int where)
{
	if (where == 0)
	{
		signal(SIGINT, ft_nothing);
		signal(SIGQUIT, ft_nothing);
	}
	if (where == 1)
	{
		signal(SIGINT, ft_restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (where == 2)
	{
		signal(SIGINT, ft_ctrl_c);
		signal(SIGQUIT, ft_backslash);
	}
	if (where == 3)
	{
		signal(SIGINT, ft_sig_exit);
		signal(SIGQUIT, SIG_DFL);
	}
}

void	ft_restore_prompt(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \n", STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_shell.exit_status = 1;
}

void	ft_backslash(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	g_shell.exit_status = 131;
}

void	ft_ctrl_c(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	g_shell.exit_status = 130;
}

void	ft_received_ctrl_d(t_cmd **cmd)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cmd)
		ft_free_cmds(cmd);
	ft_free_2d_array(g_shell.env);
	exit(g_shell.exit_status);
}
