/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 12:39:58 by ccestini          #+#    #+#             */
/*   Updated: 2022/09/21 14:14:03 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countnbr(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	nb;

	nb = n;
	i = ft_countnbr(nb);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	str[i] = '\0';
	i = i - 1;
	while (nb > 0)
	{
		str[i] = nb % 10 + '0';
		i--;
		nb = nb / 10;
	}
	if (n == 0)
		str[0] = '0';
	return (str);
}
