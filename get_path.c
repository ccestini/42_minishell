/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:11:35 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/10 17:19:13 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	ft_fill_path_cmds(t_cmd **cmd);
char	*ft_get_path(t_cmd **cmd);
char	*ft_check_cmd_paths_table(t_cmd **cmd);
char	*ft_check_cmd_path(t_cmd **cmd);
char	*ft_strjoin_path(char *s1, char *s2);

void	ft_fill_path_cmds(t_cmd **cmd)
{
	t_cmd	*ptr;

	ptr = (*cmd);
	while (ptr)
	{
		if (ft_check_is_builtin_parent(ptr) == 1 || \
			ft_strcmp(ptr->args[0], "pwd") == 0 || \
			ft_strcmp(ptr->args[0], "echo") == 0 || \
			ft_strcmp(ptr->args[0], "env") == 0)
		{
			ptr = ptr->next;
		}
		else
		{
			ptr->cmd_path = ft_get_path(&ptr);
			ptr = ptr->next;
		}
	}
}

char	*ft_get_path(t_cmd **cmd)
{
	if ((*cmd)->args[0] == NULL)
	{
		return (NULL);
	}
	else if ((*cmd)->args[0][0] == '/' || \
		((*cmd)->args[0][0] == '.' && (*cmd)->args[0][1] == '/'))
	{
		(*cmd)->cmd_path = ft_check_cmd_path(cmd);
		return ((*cmd)->cmd_path);
	}
	else
	{
		(*cmd)->cmd_path = ft_check_cmd_paths_table(cmd);
		return ((*cmd)->cmd_path);
	}
}

char	*ft_check_cmd_paths_table(t_cmd **cmd)
{
	char	*all_paths;
	char	**paths_table;
	int		i;

	i = -1;
	all_paths = ft_getenv("PATH");
	if (all_paths[0] == '\0')
	{
		free(all_paths);
		return ((*cmd)->cmd_path);
	}
	paths_table = ft_split(all_paths, ':');
	while (paths_table && paths_table[++i])
	{
		paths_table[i] = ft_strjoin_path(paths_table[i], (*cmd)->args[0]);
		if (access(paths_table[i], F_OK) == 0)
		{
			(*cmd)->cmd_path = ft_strdup(paths_table[i]);
			ft_free_2d_array(paths_table);
			return ((*cmd)->cmd_path);
		}
	}
	(*cmd)->cmd_path = NULL;
	ft_free_2d_array(paths_table);
	return ((*cmd)->cmd_path);
}

char	*ft_check_cmd_path(t_cmd **cmd)
{
	if (access((*cmd)->args[0], F_OK) == 0)
	{
		(*cmd)->cmd_path = ft_strdup((*cmd)->args[0]);
		return ((*cmd)->cmd_path);
	}
	else
	{
		(*cmd)->cmd_path = NULL;
		g_shell.exit_status = 127;
		return ((*cmd)->cmd_path);
	}
}

char	*ft_strjoin_path(char *s1, char *s2)
{
	char	*new_s;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	new_s = ft_calloc(sizeof(char), (ft_strlen(s1) + (ft_strlen(s2) + 2)));
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		new_s[i] = s1[i];
		i++;
	}
	if (new_s[i - 1] != '/')
	{
		new_s[i] = '/';
		i++;
	}
	while (s2[j] != '\0')
		new_s[i++] = s2[j++];
	new_s[i] = '\0';
	free(s1);
	return (new_s);
}
