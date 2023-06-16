/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:22:17 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/09 14:12:53 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_check_args(int ac, char *av[], char *envp[]);
int		ft_check_only_space(char *line);

int	main(int ac, char *av[], char *envp[])
{
	char	*line;

	g_shell.env = ft_check_args(ac, av, envp);
	line = NULL;
	while (1)
	{
		ft_signals_received(1);
		line = readline("\001\033[33m\002" "my@shell-> " "\001\033[0m\002");
		if (line == NULL)
			ft_received_ctrl_d(&g_shell.cmds);
		if (ft_strlen(line) > 0 && line[0] != '\0')
		{
			if (ft_check_only_space(line) == 1)
				continue ;
			add_history(line);
			ft_parse_line(line);
		}
		ft_free_cmds_and_line(&g_shell.cmds, line);
	}
	rl_clear_history();
	ft_free_2d_array(g_shell.env);
	return (0);
}

char	**ft_check_args(int ac, char *av[], char *envp[])
{
	if (ac != 1 || !av[0])
	{
		ft_putstr_fd("Error: To run my@shell type only-> ./minishell\n", \
			STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (!envp[0])
	{
		exit(EXIT_FAILURE);
	}
	g_shell.env = ft_copy_env(envp);
	return (g_shell.env);
}

int	ft_check_only_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
