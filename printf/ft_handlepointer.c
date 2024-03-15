/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlepointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 21:37:55 by Eva               #+#    #+#             */
/*   Updated: 2023/11/16 09:25:50 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

int	decimal_to_hex_p(uintptr_t ptr_dec, int *len, char *set, int i)
{
	char	temp[20];
	int		remainder;

	if (ptr_dec == 0)
	{
		temp[i++] = '0';
	}
	else
	{
		while (ptr_dec > 0)
		{
			remainder = ptr_dec % 16;
			temp[i++] = set[remainder];
			ptr_dec /= 16;
		}
	}
	temp[i] = '\0';
	while (--i >= 0)
	{
		if (my_putchar(temp[i], len) == -1)
			return (-1);
	}
	return (*len);
}

int	handlepointer(va_list args, int *len)
{
	void		*ptr;
	uintptr_t	ptr_dec;
	char		*set;
	int			i;

	set = "0123456789abcdef";
	i = 0;
	(void)len;
	ptr = va_arg(args, void *);
	ptr_dec = (uintptr_t)ptr;
	if (my_putchar('0', len) == -1)
		return (-1);
	if (my_putchar('x', len) == -1)
		return (-1);
	if (decimal_to_hex_p(ptr_dec, len, set, i) == -1)
		return (-1);
	return (*len);
}
