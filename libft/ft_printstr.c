/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:03:54 by ccestini          #+#    #+#             */
/*   Updated: 2022/05/10 12:29:31 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printstr(char *str)
{
	int		len;
	char	*s;

	len = 0;
	s = "(null)";
	if (str == 0)
	{
		write (1, s, 6);
		return (6);
	}
	while (str[len] != '\0')
		len++;
	write (1, str, len);
	return (len);
}
