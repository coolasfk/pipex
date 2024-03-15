/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:41:50 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/03/12 19:30:53 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_strdup(char *s1);
char	*ft_substr(char *s, unsigned int strt, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *s, char c);
int		ft_strncmp(char *s1, char *s2, size_t n);
size_t	ft_strlen(char *str);

#endif
