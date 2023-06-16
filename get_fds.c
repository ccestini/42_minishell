/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:41:59 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/13 18:45:51 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_update_fd(char **str, int i, t_cmd *cmd);
int		ft_check_open_fds(int fd);
int		ft_do_heredoc(t_cmd *cmd, char **envp, char **str, int i);
int		ft_do_redirections(t_cmd *cmd, char **str, int i);

int	ft_update_fd(char **str, int i, t_cmd *cmd)
{
	char	*temp;

	if (str[i + 1])
		temp = str[i + 1];
	if (ft_strcmp(str[i], "<<") == 0 && str[i + 1])
	{
		return (ft_do_heredoc(cmd, g_shell.env, str, i));
	}
	else
	{
		if (str[i + 1])
			str[i + 1] = ft_strtrim(str[i + 1], "\'\"");
		free (temp);
		return (ft_do_redirections(cmd, str, i));
	}
	free (temp);
	return (i + 1);
}

int	ft_do_heredoc(t_cmd *cmd, char **envp, char **str, int i)
{
	int	hd;

	cmd->heredoc_delimiter = ft_strdup(str[i + 1]);
	hd = ft_get_heredoc_fd(&cmd, envp);
	if (hd == -1)
		ft_exit_heredoc(&cmd);
	cmd->input_fd = open("heredoc_input", O_RDONLY);
	if (ft_check_open_fds(cmd->input_fd) == -1)
		return (-1);
	unlink("heredoc_input");
	return (i + 1);
}

int	ft_do_redirections(t_cmd *cmd, char **str, int i)
{
	if (ft_strcmp(str[i], ">") == 0 && str[i + 1])
	{
		if (cmd->output_fd > 0)
			close(cmd->output_fd);
		cmd->output_fd = open(str[i + 1], O_TRUNC | O_WRONLY | O_CREAT, 0777);
		if (ft_check_open_fds(cmd->output_fd) == -1)
			return (-1);
	}
	else if (ft_strcmp(str[i], "<") == 0 && str[i + 1])
	{
		if (cmd->input_fd > 0)
			close(cmd->input_fd);
		cmd->input_fd = open(str[i + 1], O_RDONLY);
		if (ft_check_open_fds(cmd->input_fd) == -1)
			return (-1);
	}
	else if (ft_strcmp(str[i], ">>") == 0 && str[i + 1])
	{
		if (cmd->output_fd > 0)
			close(cmd->output_fd);
		cmd->output_fd = open(str[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0777);
		if (ft_check_open_fds(cmd->output_fd) == -1)
			return (-1);
	}
	return (i + 1);
}

int	ft_check_open_fds(int fd)
{
	if (fd < 0)
	{
		perror("my@shell: ");
		g_shell.exit_status = 1;
		return (-1);
	}
	return (0);
}
