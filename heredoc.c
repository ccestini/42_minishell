/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:56:12 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/10 17:19:45 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int		ft_get_heredoc_fd(t_cmd **cmd, char **envp);
char	*ft_get_heredoc_loop(t_cmd **cmd, char **envp, char *line, int fd);
int		ft_check_delimiter(t_cmd **cmd);

int	ft_get_heredoc_fd(t_cmd **cmd, char **envp)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open("heredoc_input", O_TRUNC | O_WRONLY | O_CREAT, 0777);
	ft_check_open_fds(fd);
	if (ft_check_delimiter(cmd) == -1)
	{
		close(fd);
		return (-1);
	}
	if ((*cmd)->heredoc_flag_exp == 0)
		ft_trim_heredoc_delimiter(cmd);
	line = ft_get_heredoc_loop(cmd, envp, line, fd);
	if (line)
		free(line);
	close(fd);
	return (0);
}

char	*ft_get_heredoc_loop(t_cmd **cmd, char **envp, char *line, int fd)
{
	int		len_delimiter;

	len_delimiter = ft_strlen((*cmd)->heredoc_delimiter);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_received_ctrl_d_heredoc();
			break ;
		}
		if ((*cmd)->heredoc_flag_exp == 1)
			line = ft_dollar_expansion_x(line, envp);
		if (((!ft_strncmp((*cmd)->heredoc_delimiter, \
			line, len_delimiter))) && (line[len_delimiter] == '\0'))
			break ;
		write (fd, line, ft_strlen(line));
		write (fd, "\n", 1);
		if (line)
			free(line);
	}
	return (line);
}

int	ft_check_delimiter(t_cmd **cmd)
{
	int		i;
	char	*s;

	i = 0;
	s = (*cmd)->heredoc_delimiter;
	if (s[0] == '-')
	{
		ft_putstr_fd("my@shell: option not supported for heredocs\n", 2);
		g_shell.exit_status = 1;
		return (-1);
	}
	if (s[0] == '\\')
		(*cmd)->heredoc_flag_exp = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == '\"' || s[i] == '\'') && s[i] != '\0')
		{
			i = ft_find_quotes_heredoc(s, i);
			(*cmd)->heredoc_flag_exp = 0;
			if (i == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}
