/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:31:48 by eprzybyl          #+#    #+#             */
/*   Updated: 2023/11/16 10:20:08 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_printf.h"

int	switch_cases(char specifier, va_list args, int *len)
{
	int	c;
	int	switch_f_check;

	if (specifier == 's')
		switch_f_check = handlestr(args, len);
	if (specifier == 'c')
	{
		c = va_arg(args, int);
		switch_f_check = my_putchar(c, len);
	}
	if (specifier == 'p')
		switch_f_check = handlepointer(args, len);
	if (specifier == 'i' || specifier == 'd')
		switch_f_check = handlenum(args, len);
	if (specifier == 'u')
		switch_f_check = handleuint(args, len);
	if (specifier == 'x' || specifier == 'X')
		switch_f_check = handlehex(args, len, specifier);
	if (specifier == '%')
		switch_f_check = my_putchar('%', len);
	if (switch_f_check == -1)
		return (-1);
	return (*len);
}

int	loop_f(const char *format, va_list args, int *len)
{
	while (*format)
	{
		if (*format == '%')
		{
			if (switch_cases(*(++format), args, len) == -1)
			{
				va_end(args);
				return (-1);
			}
		}
		else if (my_putchar(*format, len) == -1)
		{
			va_end(args);
			return (-1);
		}
		format++;
	}
	return (*len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	if (!format)
		return (-1);
	len = 0;
	va_start(args, format);
	if (loop_f(format, args, &len) == -1)
		return (-1);
	va_end(args);
	return (len);
}
