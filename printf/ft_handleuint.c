/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handleuint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:39:19 by eprzybyl          #+#    #+#             */
/*   Updated: 2023/11/16 09:19:59 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

int	putnum(unsigned int num, int *len)
{
	if (num > 9)
	{
		if (putnum(num / 10, len) == -1)
			return (-1);
		if (my_putchar(num % 10 + '0', len) == -1)
			return (-1);
	}
	else
	{
		if (my_putchar(num + '0', len) == -1)
			return (-1);
	}
	return (*len);
}

int	handleuint(va_list args, int *len)
{
	unsigned int	num;

	num = va_arg(args, unsigned int);
	if (putnum(num, len) == -1)
		return (-1);
	return (*len);
}
