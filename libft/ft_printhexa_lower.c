/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa_lower.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:25:17 by ccestini          #+#    #+#             */
/*   Updated: 2022/09/21 14:15:30 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printhexa_lower(unsigned int n)
{
	char	*hexa;
	int		len;

	len = 0;
	hexa = "0123456789abcdef";
	if (n >= 16)
		len = len + ft_printhexa_lower(n / 16);
	len = len + write(1, &hexa[n % 16], 1);
	return (len);
}
