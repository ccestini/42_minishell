/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:41:28 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/02 17:43:17 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sub;

	if (!s)
		return (0);
	if (start > ft_strlen(s) || len <= 0)
		return (ft_strdup(""));
	if (len <= ft_strlen(s))
		sub = ft_calloc((len + 1), sizeof(char));
	else
		sub = ft_calloc(sizeof(char), (ft_strlen(s) + 1 - start));
	if (!sub)
		return (0);
	i = start;
	j = 0;
	while (j < len && i < ft_strlen(s))
		sub[j++] = s[i++];
	sub[j] = '\0';
	return (sub);
}
