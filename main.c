/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:14:41 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/03/17 17:59:04 by eprzybyl         ###   ########.fr       */
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

void	initialize_var(t_p *p, char *envp[], char *argv[])
{
	p->cmd1 = ft_split(argv[2], ' ');
	p->cmd2 = ft_split(argv[3], ' ');
	p->envp = envp;
	p->i = 0;
	p->result = -9;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_p	p;
	int	status;
	int	childExitStatus;

	initialize_var(&p, envp, argv);
	if (argc != 5)
	{
		exit(1);
	}
	if (pipe(p.pfd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	p.f2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (p.f2 < 0)
	{
		perror("Error opening outfile");
		exit(EXIT_FAILURE);
	}
	find_path(&p, envp);
	p.f1 = open(argv[1], O_RDONLY);
	if (p.f1 < 0)
	{
		perror("Error opening infile");
		exit(EXIT_FAILURE);
	}
	p.pid = fork();
	if (p.pid == 0)
	{
		close(p.pfd[0]);
		close(p.f2);
		dup2(p.f1, STDIN_FILENO);
		dup2(p.pfd[1], STDOUT_FILENO);
		p.result = process_possible(&p, p.cmd1);
		exit(p.result);
	}
	else
	{
		close(p.pfd[1]);
		wait(NULL);
		p.pid = fork();
		if (p.pid == 0)
		{
			close(p.f1);
			dup2(p.pfd[0], STDIN_FILENO);
			dup2(p.f2, STDOUT_FILENO);
			p.result = process_possible(&p, p.cmd2);
		}
	}
	waitpid(p.pid, &status, 0);
	if (WIFEXITED(status))
	{
		childExitStatus = WEXITSTATUS(status);
		if (childExitStatus != 0)
		{
			free_memory(&p);
			exit(childExitStatus);
		}
	}
	close(p.f1);
	close(p.f2);
	close(p.pfd[0]);
	//wait(NULL);
	free_memory(&p);
	return (0);
}

void	free_memory(t_p *p)
{
	free(p->path);
	free(p->cmd1);
	free(p->cmd2);
}

int	process_possible(t_p *p, char **cmd)
{
	char	*path;
	char	*temp_path;

	p->i = 0;
	while (p->path[p->i] != NULL)
	{
		temp_path = ft_strjoin(p->path[p->i], "/");
		path = ft_strjoin(temp_path, cmd[0]);
		free(temp_path);
		temp_path = NULL;
		if (!path)
			exit(127);
		if (access(path, X_OK) == 0)
			break ;
		p->i++;
	}
	if (execve(path, cmd, p->envp) == -1)
	{
		perror("execve failed");
		exit(127);
	}
	free(path);
	exit(127);
	return (0);
}
