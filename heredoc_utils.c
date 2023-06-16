/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:27:01 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/10 16:59:28 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*ft_trim_heredoc_delimiter(t_cmd **cmd);
int		ft_find_quotes_heredoc(char *s, int i);
void	ft_exit_heredoc(t_cmd **cmd);
void	ft_received_ctrl_d_heredoc(void);
void	ft_handle_ctrl_c_heredoc(int signbr);

int	ft_find_quotes_heredoc(char *s, int i)
{
	char	c;

	c = s[i];
	i++;
	while (s[i] != c && s[i] != '\0')
		i++;
	if (s[i] == '\0')
	{
		ft_putstr_fd("my@shell: open quote not supported for heredoc\n", \
					STDERR_FILENO);
		g_shell.exit_status = 1;
		return (-1);
	}
	return (i);
}

char	*ft_trim_heredoc_delimiter(t_cmd **cmd)
{
	char	*new_delimiter;

	new_delimiter = ft_strtrim((*cmd)->heredoc_delimiter, "\'\"\\");
	free((*cmd)->heredoc_delimiter);
	(*cmd)->heredoc_delimiter = new_delimiter;
	return ((*cmd)->heredoc_delimiter);
}

void	ft_exit_heredoc(t_cmd **cmd)
{
	ft_free_cmds(cmd);
	g_shell.exit_status = 0;
	rl_on_new_line();
}

void	ft_received_ctrl_d_heredoc(void)
{
	g_shell.exit_status = 0;
}
