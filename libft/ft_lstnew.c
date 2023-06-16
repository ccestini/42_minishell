/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:54:20 by ccestini          #+#    #+#             */
/*   Updated: 2022/02/15 12:04:59 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = NULL;
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (0);
	else
	{
		new->content = content;
		new->next = NULL;
		return (new);
	}
}
/*
Funcao para criar uma nova linked list.
Primeiro foi criado um node '*new', tbm iniciada com NULL e
depois foi alocada memoria para o node.
Testar se caso a memoria nao foi alocada e retornar NULL.
Se a alocacao da memoria der certo, prosseguimos e passamos
o valor do parametro 'content' no novo node 'new',
dentro do conteudo desse node.
Apos passamos o endereco NULL para o link do new node (pois
nao tera link, ja q eh o unico...).
O retorno eh o novo ponteiro 'new' apontando para nossa
nova lista. Esse 'new' eh como se fosse o head apontando
para o primeiro node de uma lista.
*/