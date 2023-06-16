/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccestini <ccestini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 12:11:07 by ccestini          #+#    #+#             */
/*   Updated: 2022/05/10 12:28:30 by ccestini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_format(va_list args, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len = len + ft_printchar(va_arg(args, int));
	else if (format == 's')
		len = len + ft_printstr(va_arg(args, char *));
	else if (format == 'd' || format == 'i')
		len = len + ft_printnbr(va_arg(args, int));
	else if (format == 'u')
		len = len + ft_printunbr(va_arg(args, unsigned int));
	else if (format == 'x')
		len = len + ft_printhexa_lower(va_arg(args, unsigned int));
	else if (format == 'X')
		len = len + ft_printhexa_upper(va_arg(args, unsigned int));
	else if (format == 'p')
		len = len + ft_printptr(va_arg(args, void *));
	else if (format == '%')
		len = len + ft_printperc();
	else
		len = len + ft_printchar(format);
	return (len);
}
/*
Essa funcao foi criada para ler o caracter que vem apos o caracter '%'
e chamar a funcao que fara o output de acordo com seu formato.
    c = va_arg(args, int);
    s = va_arg(args, char *);
    d = va_arg(args, int);
    i = va_arg(args, int);
    u = va_arg(args, unsigned int);
    p = va_arg(args, void *);
    x = va_arg(args, unsigned int);
    X = va_arg(args, unsigned int);
*/
