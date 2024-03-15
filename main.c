/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:14:41 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/03/15 16:13:45 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/pipex.h"

void	errors(int code)
{
	if (code == 1)
		fprintf(stderr, "Usage: %s file1 cmd1 cmd2 file2\n", "too little argc");
	if (code == 2)
		fprintf(stderr, "%s\n", "pipe error");
}

#include "pipex.h"

char	**find_path(t_p *p, char *envp[])
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = envp[i];
		i++;
	}
	if (!path)
		return (NULL);
	p->path = ft_split(path, ':');
	if (!p->path)
	{
		ft_printf("Error splitting PATH variable.\n");
		return (NULL);
	}
	return (p->path);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_p	p;
	int	pfd[2];

	p.cmd1 = ft_split(argv[2], ' ');
	p.cmd2 = ft_split(argv[3], ' ');
	p.envp = envp;
	if (argc != 5)
	{
		errors(1);
		return (-1);
	}
	if (pipe(pfd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	p.f2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (p.f2 < 0)
	{
		perror("Error opening outfile.txt");
		exit(EXIT_FAILURE);
	}
	find_path(&p, envp);
	p.f1 = open(argv[1], O_RDONLY);
	p.pid = fork();
	if (p.pid == 0)
	{
		close(pfd[0]);
		close(p.f2);
		dup2(p.f1, STDIN_FILENO);
		dup2(pfd[1], STDOUT_FILENO);
		process_possible(&p, p.cmd1);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pfd[1]);
		wait(NULL);
		p.pid = fork();
		if (p.pid == 0)
		{
			close(p.f1);
			dup2(pfd[0], STDIN_FILENO);
			dup2(p.f2, STDOUT_FILENO);
			process_possible(&p, p.cmd2);
			exit(EXIT_SUCCESS);
		}
	}
	close(p.f1);
	close(p.f2);
	close(pfd[0]);
	wait(NULL);
	return (0);
}

int	process_possible(t_p *p, char **cmd)
{
	int		i;
	char	*path;
	char	*temp_path;

	i = 0;
	while (p->path[i] != NULL)
	{
		temp_path = ft_strjoin(p->path[i], "/");
		path = ft_strjoin(temp_path, cmd[0]);
		if (!path)
			return (-1);
		if (access(path, X_OK) == 0)
			break ;
		i++;
	}
	free(temp_path);
	if (execve(path, cmd, p->envp) == -1)
		perror("execve failed");
	free(path);
	return (-1);
}
