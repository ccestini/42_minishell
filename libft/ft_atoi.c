/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 16:39:22 by ccestini          #+#    #+#             */
/*   Updated: 2022/09/21 14:13:05 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

int	ft_atoi(const char *str)
{
	unsigned long	c;
	unsigned long	r;
	long			s;

	c = 0;
	r = 0;
	s = 1;
	while ((str[c] == ' ') || (str[c] == '\t') || (str[c] == '\r')
		|| (str[c] == '\n') || (str[c] == '\v') || (str[c] == '\f'))
		c++;
	if ((str[c] == '-') || (str[c] == '+'))
	{
		if (str[c++] == '-')
			s *= -1;
	}
	while ((str[c] >= '0') && (str[c] <= '9'))
		r = (str[c++] - '0') + (r * 10);
	if (r > 2147483648 && s == -1)
		return (0);
	if (r > 2147483647 && s == 1)
		return (-1);
	return (r * s);
}
