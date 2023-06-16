/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:42:19 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/10 13:25:37 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int		ft_builtin_echo(t_cmd **cmd, int fds[], int pid[]);
int		ft_check_args_echo(char **str, int i);
int		ft_check_echo_option(char **args);

int	ft_builtin_echo(t_cmd **cmd, int fds[], int pid[])
{
	int	i;
	int	option;
	int	nbr_pipes;	

	nbr_pipes = ft_lstcmd_size(*cmd);
	option = ft_check_echo_option((*cmd)->args);
	if (option == 0)
		i = 1;
	else
		i = 2;
	i = ft_check_args_echo((*cmd)->args, i);
	while ((*cmd)->args && (*cmd)->args[i])
	{
		ft_putstr_fd((*cmd)->args[i], STDOUT_FILENO);
		if ((*cmd)->args && (*cmd)->args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (option == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	ft_clean_child_builtin(cmd, nbr_pipes, fds);
	if (pid)
		free(pid);
	exit (g_shell.exit_status);
}

int	ft_check_args_echo(char **str, int i)
{
	int	j;

	j = 0;
	while (str && str[i])
	{
		if (str[i] && (ft_strcmp(str[i], "-n") == 0))
			i++;
		else if (str[i] && (str[i][j] == '-' && str[i][j + 1] == 'n'))
		{
			j++;
			while (str[i] && str[i][j] == 'n')
				j++;
			if (str[i][j] == '\0')
			{
				i++;
				continue ;
			}
			else
				return (i);
		}
		else
			return (i);
	}
	return (i);
}

int	ft_check_echo_option(char **args)
{
	int	i;
	int	option;

	i = 2;
	option = 0;
	if (args && args[1])
	{
		if (args[1][0] == '-' && args[1][1] == 'n')
		{
			if (args[1][2] == '\0')
				option = 1;
			else
			{
				while (args[1][i] && args[1][i] == 'n')
					i++;
				if (args[1][i] == '\0')
					option = 1;
				else if (args[1][i] != '\0' && args[1][i] != 'n')
					option = 0;
			}
		}
	}
	return (option);
}
