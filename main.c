/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:14:41 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/03/17 19:26:48 by eprzybyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		free_memory(p);
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
	if (pipe(p->pfd) == -1)
	{
		perror("pipe");
		free_memory(p);
		exit(EXIT_FAILURE);
	}
	p->f2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (p->f2 < 0)
	{
		perror("Error opening outfile");
		free_memory(p);
		exit(EXIT_FAILURE);
	}
	p->f1 = open(argv[1], O_RDONLY);
	if (p->f1 < 0)
	{
		perror("Error opening infile");
		free_memory(p);
		exit(EXIT_FAILURE);
	}
	p->path = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_p	p;
	int	childExitStatus;

	if (argc != 5)
		exit(1);
	initialize_var(&p, envp, argv);
	find_path(&p, envp);
	p.pid = fork();
	if (p.pid == 0)
	{
		close(p.pfd[0]);
		close(p.f2);
		dup2(p.f1, STDIN_FILENO);
		dup2(p.pfd[1], STDOUT_FILENO);
		p.result = process_possible(&p, p.cmd1);
		free(p.cmd1);
		free(p.path);
		free_memory(&p);
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
	close(p.f1);
	close(p.f2);
	close(p.pfd[0]);
	free_memory(&p);
	waitpid(p.pid, &p.status, 0);
	if (WIFEXITED(p.status))
	{
		childExitStatus = WEXITSTATUS(p.status);
		if (childExitStatus != 0)
		{
			exit(childExitStatus);
		}
	}
	return (0);
}

void	free_memory(t_p *p)
{
	int	i;

	i = 0;
	if (p->path != NULL)
	{
		while (p->path[i] != NULL)
		{
			free(p->path[i]);
			i++;
		}
		free(p->path);
	}
	i = 0;
	if (p->cmd1 != NULL)
	{
		while (p->cmd1[i] != NULL)
		{
			free(p->cmd1[i]);
			i++;
		}
		free(p->cmd1);
	}
	i = 0;
	if (p->cmd2 != NULL)
	{
		while (p->cmd2[i] != NULL)
		{
			free(p->cmd2[i]);
			i++;
		}
		free(p->cmd2);
	}

}

int	process_possible(t_p *p, char **cmd)
{
	char	*temp_path;

	p->i = 0;
	while (p->path[p->i] != NULL)
	{
		temp_path = ft_strjoin(p->path[p->i], "/");
		p->cmd_path = ft_strjoin(temp_path, cmd[0]);
		free(temp_path);
		temp_path = NULL;
		if (!p->cmd_path)
		{
			free_memory(p);
			exit(127);
		}
		if (access(p->cmd_path, X_OK) == 0)
			break ;
		free(p->cmd_path);
		p->cmd_path = NULL;
		p->i++;
	}
	if (execve(p->cmd_path, cmd, p->envp) == -1)
	{
		free_memory(p);
		perror("execve failed");
		exit(127);
	}
	exit(127);
	return (0);
}
