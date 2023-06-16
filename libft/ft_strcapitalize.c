/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 13:20:55 by ccestini          #+#    #+#             */
/*   Updated: 2022/09/23 12:54:50 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strlowcase(char *str)
{
	int	e;

	e = 0;
	while (str[e] != '\0')
	{
		if ((str[e] >= 'A') && (str[e] <= 'Z'))
			str[e] = str[e] + 32;
		e++;
	}
	return (str);
}

char	*ft_strcapitalize(char *str)
{	
	int	el;

	el = 0;
	ft_strlowcase(str);
	while (str[el] != '\0')
	{
		if (((str[el] < '0') || (str[el] > 'z'))
			|| ((str[el] > '9') && (str[el] < 'A'))
			|| ((str[el] > 'Z') && (str[el] < 'a')))
		{
			if ((str[el + 1] >= 'a') && (str[el + 1] <= 'z'))
				str[el + 1] = str [el + 1] - 32;
		}
		el++;
	}
	if ((str[0] != '\0') && (str[0] >= 'a') && (str[0] <= 'z'))
	{
		str[0] = str[0] - 32;
	}
	return (str);
}
