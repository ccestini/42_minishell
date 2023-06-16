/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:04:00 by ccestini          #+#    #+#             */
/*   Updated: 2022/09/21 14:15:57 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printunbr(unsigned int n)
{
	char	*nbr;
	int		len;

	len = 1;
	nbr = "0123456789";
	if (n >= 10)
		len = len + ft_printunbr(n / 10);
	write(1, &nbr[n % 10], 1);
	return (len);
}
