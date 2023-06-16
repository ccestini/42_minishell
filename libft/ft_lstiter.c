/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:56:48 by ccestini          #+#    #+#             */
/*   Updated: 2022/02/15 12:01:44 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
/*
Funcao que replica a lista 'lst' e aplica uma funcao 'f'
para o content de cada node.
Paramentro 'lst' eh o endereco para um node; 2. endereco
da funcao f usada para replicar a lista.
*/