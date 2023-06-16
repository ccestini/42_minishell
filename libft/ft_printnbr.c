/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:03:30 by ccestini          #+#    #+#             */
/*   Updated: 2022/09/21 14:15:42 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printnbr(int n)
{
	char	*nbr;
	int		len;

	len = 0;
	nbr = "0123456789";
	if (n == -2147483648)
	{
		write (1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		len = len + write (1, "-", 1);
		n = -n;
	}
	if (n >= 10)
		len = len + ft_printnbr(n / 10);
	len = len + write(1, &nbr[n % 10], 1);
	return (len);
}
