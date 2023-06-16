/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:08:22 by ccestini          #+#    #+#             */
/*   Updated: 2023/02/02 17:45:39 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	int		i;
	int		j;
	int		n;

	if (!s1 || !s2)
		return (0);
	new_s = ft_calloc((sizeof(char)), (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_s)
		return (0);
	i = 0;
	n = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		new_s[n] = s1[i];
		n++;
		i++;
	}
	while (s2[j] != '\0')
	{
		new_s[n++] = s2[j++];
	}
	new_s[n] = '\0';
	return (new_s);
}
