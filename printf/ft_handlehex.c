/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlehex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:57:03 by eprzybyl          #+#    #+#             */
/*   Updated: 2023/11/16 09:20:52 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

int	decimal_to_hex(unsigned int num, int *len, char *set)
{
	int		remainder;
	char	temp[20];
	int		i;

	i = 0;
	if (num == 0)
	{
		temp[i++] = '0';
	}
	while (num > 0)
	{
		remainder = num % 16;
		temp[i++] = set[remainder];
		num /= 16;
	}
	temp[i] = '\0';
	i -= 1;
	while (i >= 0)
		if (my_putchar(temp[i--], len) == -1)
			return (-1);
	return (*len);
}

int	handlehex(va_list args, int *len, char specifier)
{
	unsigned int	num;
	char			*set;

	set = NULL;
	num = va_arg(args, unsigned int);
	if (specifier == 'x')
	{
		set = "0123456789abcdef";
	}
	else if (specifier == 'X')
	{
		set = "0123456789ABCDEF";
	}
	if (decimal_to_hex(num, len, set) == -1)
		return (-1);
	return (*len);
}
