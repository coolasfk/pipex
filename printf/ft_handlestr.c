/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlestr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:32:17 by eprzybyl          #+#    #+#             */
/*   Updated: 2023/11/16 09:05:20 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

int	handlestr(va_list args, int *len)
{
	char	*str;

	str = va_arg(args, char *);
	if (str == NULL)
	{
		str = "(null)";
	}
	while (*str != '\0')
	{
		if (my_putchar(*str++, len) == -1)
		{
			return (-1);
		}
	}
	return (*len);
}
