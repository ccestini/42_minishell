/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:56:54 by ccestini          #+#    #+#             */
/*   Updated: 2022/02/15 13:48:50 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	(del)(lst->content);
	free(lst);
}
/*
Funcao que deleta e libera a memoria de um elemento, usando
uma funcao 'del'. O proximo node nao deve ser apagado.
PARAMETROS:1. The element to free; 2. The address of the function
used to delete the content.
*/