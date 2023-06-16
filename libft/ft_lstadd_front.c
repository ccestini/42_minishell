/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:01:19 by ccestini          #+#    #+#             */
/*   Updated: 2022/02/15 12:01:31 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		temp = new;
		temp->next = *lst;
		*lst = temp;
	}
}
/*
Funcao para adicionar um novo elemento 'new' no comeco da lista.
PARAMETROS: 1. The address of a pointer to the first link of a list;
2. The address of a pointer to the element to be added to the list.
*/