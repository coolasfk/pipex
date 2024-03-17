/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:34:33 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/03/17 20:36:55 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	initialize_var(t_p *p, char *envp[], char *argv[])
{
	p->f2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (p->f2 < 0)
	{
		perror("Error opening outfile");
		exit(EXIT_FAILURE);
	}
	p->f1 = open(argv[1], O_RDONLY);
	if (p->f1 < 0)
	{
		perror("Error opening infile");
		exit(EXIT_FAILURE);
	}
	p->cmd1 = ft_split(argv[2], ' ');
	p->cmd2 = ft_split(argv[3], ' ');
	p->envp = envp;
	p->i = 0;
	p->result = -9;
	if (pipe(p->pfd) == -1)
	{
		perror("pipe");
		free_memory(p);
		exit(EXIT_FAILURE);
	}
}

void	free_memory(t_p *p)
{
	free_array(p->path);
	free_array(p->cmd1);
	free_array(p->cmd2);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array != NULL)
	{
		while (array[i] != NULL)
		{
			free(array[i]);
			i++;
		}
		if (array != NULL)
			free(array);
		array = NULL;
	}
}
