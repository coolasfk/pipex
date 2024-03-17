/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 10:13:39 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/03/17 20:38:55 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char *s, char c)
{
	int	i;
	int	word_count;

	word_count = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
			word_count++;
		i++;
	}
	return (word_count);
}

char	*free_split(char **split, int word_count)
{
	while (word_count > 0)
	{
		free(split[word_count - 1]);
		word_count--;
	}
	free(split);
	return (NULL);
}

char	**populate_split(char *s, char c, char **split, int word_count)
{
	int	i;
	int	start;
	int	len;

	i = 0;
	word_count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			start = i;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			len = i - start + 1;
			split[word_count] = ft_substr((char *)s, start, len);
			if (!split[word_count])
			{
				free_split(split, word_count);
				return (NULL);
			}
			word_count++;
		}
		i++;
	}
	split[word_count] = NULL;
	return (split);
}

char	**ft_split(char *s, char c)
{
	int		word_count;
	char	**split;

	word_count = count_words(s, c);
	split = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split = populate_split(s, c, split, word_count);
	return (split);
}
/*
int	main(int argc, char *argv[])
{
	(void)argc;
	printf("S: %s", *ft_split(argv[1], *argv[2]));
}

*/
