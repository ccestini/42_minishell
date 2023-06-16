/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:56:51 by ccestini          #+#    #+#             */
/*   Updated: 2022/02/15 12:04:05 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*aux;

	if (!*lst)
		return ;
	while (*lst)
	{
		aux = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = aux;
	}
	*lst = NULL;
}
/*
Funcao que deleta e libera a memoria de um elemento e de
todos os elementos sucessivos, usando uma funcao 'del'.
Apos, o ponteiro da lista deve apontar para NULL.
PARAMETROS:1. The adress of a pointer to an element.; 
2. The address of the function used to delete the content.
*/