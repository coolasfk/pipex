/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:44:03 by eprzybyl          #+#    #+#             */
/*   Updated: 2023/11/15 20:54:25 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	my_putchar(int c, int *len);
int	handlepointer(va_list args, int *len);
int	handlestr(va_list args, int *len);
int	switch_cases(char specifier, va_list args, int *len);
int	decimal_to_hex(unsigned int num, int *len, char *set);
int	handlenum(va_list args, int *len);
int	num_recursive(int n, int *len);
int	putnum(unsigned int num, int *len);
int	handleuint(va_list args, int *len);
int	decimal_to_hex_p(uintptr_t ptr_dec, int *len, char *set, int i);
int	handlehex(va_list args, int *len, char specifier);

#endif