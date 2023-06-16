/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:53:18 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/09 09:54:49 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	ft_free_cmds(t_cmd **cmd);
void	ft_free_cmds_and_line(t_cmd **cmd, char *line);
void	ft_free_2d_array(char **array2d);

void	ft_free_cmds(t_cmd **cmd)
{
	t_cmd	*current;

	current = (*cmd);
	while (current != NULL)
	{
		if (current->full_str != NULL)
			free (current->full_str);
		if (current->cmd_path != NULL)
			free (current->cmd_path);
		if (current->input_filename)
			free(current->input_filename);
		if (current->output_filename)
			free(current->output_filename);
		if (current->heredoc_delimiter != NULL)
			free (current->heredoc_delimiter);
		if (current->args != NULL)
			ft_free_2d_array(current->args);
		current = current->next;
	}
	if ((*cmd) != NULL)
		ft_lstcmd_delete(cmd);
}

void	ft_free_cmds_and_line(t_cmd **cmd, char *line)
{
	if (cmd != NULL)
		ft_free_cmds(cmd);
	cmd = NULL;
	if (line != NULL)
		free (line);
	line = NULL;
}

void	ft_free_2d_array(char **array2d)
{
	int	i;

	i = 0;
	while (array2d[i])
	{
		if (array2d[i])
			free(array2d[i]);
		i++;
	}
	free(array2d);
}
