/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:11:31 by mkovoor           #+#    #+#             */
/*   Updated: 2023/02/13 18:43:34 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_parse_line(char *line);
int		ft_fill_node(t_cmd *cmd);
char	**ft_get_args_m(char **str, t_cmd *cmd);
void	ft_update_args(char **str, t_cmd *cmd, int count);
int		ft_is_redirection(char *str);

t_cmd	*ft_parse_line(char *line)
{
	t_cmd	*ptr;
	char	**split_pipe;
	int		i;

	ptr = NULL;
	if (ft_syntax_check(line) == -1)
		return (NULL);
	split_pipe = ft_split_pipes(line, '|');
	if (!split_pipe)
		return (NULL);
	i = 0;
	while (split_pipe[i] != NULL)
		ft_lstcmd_add_back(&g_shell.cmds, ft_lstcmd_new_pipe(split_pipe[i++]));
	ptr = g_shell.cmds;
	while (ptr != NULL)
	{
		ft_fill_node(ptr);
		ptr = ptr->next;
	}
	ft_free_2d_array(split_pipe);
	ft_execute_line(g_shell.cmds);
	return (g_shell.cmds);
}

int	ft_fill_node(t_cmd *cmd)
{
	char	**token_str;
	int		i;
	int		token_count;

	i = -1;
	token_str = ft_tokenize(cmd->full_str, "<>");
	token_count = ft_2d_array_len(token_str);
	cmd->args = ft_calloc(sizeof(char *), token_count + 1);
	while (token_str[++i])
		cmd->args[i] = ft_dollar_expansion_x(token_str[i], g_shell.env);
	ft_free_2d_array(token_str);
	return (0);
}

char	**ft_get_args_m(char **str, t_cmd *cmd)
{
	int	count;

	count = ft_count_strs(str);
	ft_update_args(str, cmd, count);
	return (cmd->args);
}

void	ft_update_args(char **str, t_cmd *cmd, int count)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	cmd->args = ft_calloc(sizeof(char *), (count + 2));
	while (j < count || str[i])
	{	
		if (count == 0)
			cmd->args[j++] = ft_strdup("");
		if (ft_is_redirection(str[i]))
			ft_update_fd(str, i++, cmd);
		else if (str[i][0] != '\0')
			cmd->args[j++] = ft_check_for_quotes(str[i]);
		i++;
	}
	ft_free_2d_array(str);
}

int	ft_is_redirection(char *str)
{
	if (!ft_strcmp(str, "<") || !ft_strcmp(str, ">") \
		|| !ft_strcmp(str, "<<") || !ft_strcmp(str, ">>"))
		return (1);
	else
		return (0);
}
