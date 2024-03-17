/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprzybyl <eprzybyl@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:14:41 by eprzybyl          #+#    #+#             */
/*   Updated: 2024/03/17 20:37:55 by eprzybyl         ###   ########.fr       */
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

void	processes(t_p *p)
{
	if (p->pid == 0)
	{
		close(p->pfd[0]);
		close(p->f2);
		dup2(p->f1, STDIN_FILENO);
		dup2(p->pfd[1], STDOUT_FILENO);
		p->result = process_possible(p, p->cmd1);
		exit(p->result);
	}
	else
	{
		close(p->pfd[1]);
		wait(NULL);
		p->pid = fork();
		if (p->pid == 0)
		{
			close(p->f1);
			dup2(p->pfd[0], STDIN_FILENO);
			dup2(p->f2, STDOUT_FILENO);
			p->result = process_possible(p, p->cmd2);
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_p	p;

	if (argc != 5)
	{
		ft_printf("Incorrect number of arguments%s\n", ".");
		exit(1);
	}
	initialize_var(&p, envp, argv);
	find_path(&p, envp);
	p.pid = fork();
	processes(&p);
	close(p.f1);
	close(p.f2);
	close(p.pfd[0]);
	free_memory(&p);
	waitpid(p.pid, &p.status, 0);
	if (WIFEXITED(p.status))
	{
		p.exit_status = WEXITSTATUS(p.status);
		if (p.exit_status != 0)
		{
			exit(p.exit_status);
		}
	}
	return (0);
}

int	process_possible(t_p *p, char **cmd)
{
	p->i = 0;
	while (p->path[p->i] != NULL)
	{
		p->temp_path = ft_strjoin(p->path[p->i], "/");
		p->cmd_path = ft_strjoin(p->temp_path, cmd[0]);
		free(p->temp_path);
		p->temp_path = NULL;
		if (!p->cmd_path)
			exit(127);
		if (access(p->cmd_path, X_OK) == 0)
			break ;
		free(p->cmd_path);
		p->cmd_path = NULL;
		p->i++;
	}
	if (execve(p->cmd_path, cmd, p->envp) == -1)
	{
		perror("execve failed");
		exit(127);
	}
	exit(127);
	return (0);
}
