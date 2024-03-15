/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlenum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:03:54 by eprzybyl          #+#    #+#             */
/*   Updated: 2023/11/16 08:44:01 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

int	num_recursive(int n, int *len)
{
	if (n == -2147483648)
	{
		*len += write(1, "-2147483648", 11);
		return (*len);
	}
	if (n < 0)
	{
		if (my_putchar('-', len) == -1)
			return (-1);
		n = -n;
	}
	if (n >= 10)
	{
		if (num_recursive(n / 10, len) == -1)
			return (-1);
	}
	if (my_putchar(n % 10 + '0', len) == -1)
		return (-1);
	return (*len);
}

int	handlenum(va_list args, int *len)
{
	int	n;

	n = va_arg(args, int);
	if (num_recursive(n, len) == -1)
		return (-1);
	return (*len);
}
