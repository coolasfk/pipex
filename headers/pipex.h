/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:13:52 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/03/15 15:49:36 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include "get_next_line.h"
#include "libft.h"

/* to write, read, close, access, pipe, dup, dup2, execve, fork */
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

/* malloc, free, exit */
# include <stdlib.h>

/* open, unlink */
# include <fcntl.h>

/* waitpid, wait */
# include <sys/wait.h>

/* strerror */
# include <string.h>

/*to perror*/
# include <stdio.h>

#include <errno.h>

typedef struct s_pipex
{
	int pid;
	char **path;
	int f1;
	int f2;
	char **envp;
	char **cmd1;
	char **cmd2;
}	t_p;

int main(int argc, char *argv[], char *envp[]);
size_t	ft_strlen(char *str);
int	process_possible(t_p *p, char **cmd);


#endif /* PIPEX_H */