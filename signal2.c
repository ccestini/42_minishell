/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:27:24 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/10 17:19:30 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sig_exit(int sig);
void	ft_nothing(int sig);

void	ft_sig_exit(int sig)
{
	(void)sig;
	ft_clean_child_builtin(&g_shell.cmds, 0, 0);
	exit (0);
}

void	ft_nothing(int sig)
{
	(void)sig;
}
