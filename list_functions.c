/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 11:37:13 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/06 11:02:32 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_lstcmd_new_pipe(char *str);
void	ft_lstcmd_add_back(t_cmd **lst, t_cmd *new);
int		ft_lstcmd_size(t_cmd *lst);
void	ft_lstcmd_delete(t_cmd **lst);
void	ft_lstcmd_print(t_cmd *lst);

t_cmd	*ft_lstcmd_new_pipe(char *str)
{
	t_cmd	*new;

	new = NULL;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	else
	{
		new->full_str = ft_strdup(str);
		new->cmd_path = NULL;
		new->input_fd = 0;
		new->output_fd = 0;
		new->input_filename = NULL;
		new->output_filename = NULL;
		new->heredoc_delimiter = NULL;
		new->heredoc_flag_exp = 1;
		new->args = NULL;
		new->next = NULL;
		return (new);
	}
}

void	ft_lstcmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*temp;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

int	ft_lstcmd_size(t_cmd *lst)
{
	int		count;
	t_cmd	*current;

	count = 0;
	if (!lst)
		return (0);
	current = lst;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	ft_lstcmd_delete(t_cmd **lst)
{
	t_cmd	*temp;

	if (!*lst)
		return ;
	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		if (temp)
			free (temp);
	}
	*lst = NULL;
}

void	ft_lstcmd_print(t_cmd *lst)
{
	t_cmd	*ptr;
	int		i;

	ptr = lst;
	i = 1;
	printf("each node\n");
	while (ptr)
	{
		printf("node[%d]= cmd path: %s\n", i++, ptr->cmd_path);
		ptr = ptr->next;
	}
	return ;
}
