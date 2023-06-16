/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:56:44 by ccestini          #+#    #+#             */
/*   Updated: 2022/02/15 12:39:56 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_map;
	t_list	*new;

	if (!lst)
		return (0);
	lst_map = NULL;
	while (lst)
	{
		new = ft_lstnew((*f)(lst->content));
		if (!new)
			ft_lstclear(&new, (*del));
		else
			ft_lstadd_back(&lst_map, new);
		lst = lst->next;
	}
	return (lst_map);
}
/*
Funcao que replica a lista 'lst' e aplica uma funcao 'f'
para o content de cada node ou cada elemento. Pode ser usada
a funcao 'del' para apagar algum conteudo de um node se necessario.
Parametros: 1. The adress of a pointer to an element;
2. The adress of the function used to iterate on the list;
3. The adress of the function used to delete the content
of an node if needed.
Retorna a nova lista ou entao retorna NULL se a alocacao de
memoria falhar.
*/