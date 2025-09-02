/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:12:04 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/01 22:13:23 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*int	create_pipes(int *pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (pipe(pipes + i * 2) == -1)
		{
			perror("pipe");
			return (0);
		}
		i++;
	}
	return (1);
}

void	cleanup_pipes(int *pipes, int pipes_created)
{
	int	j;

	j = 0;
	while (j < pipes_created * 2)
	{
		close(pipes[j]);
		j++;
	}
	free(pipes);
}*/

void	execute_commands(t_pipex *pipex, int *pipes, pid_t *pids, char **envp)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			perror("fork");
		else if (pids[i] == 0)
			child_process(i, pipes, pipex, envp);
		i++;
	}
}

void	wait_for_children(pid_t *pids, int count)
{
	int	i;
	int	status;

	i = 0;
	while (i < count)
	{
		if (pids[i] > 0)
			waitpid(pids[i], &status, 0);
		i++;
	}
}

void	handle_single_command(t_pipex *pipex, char **envp)
{
	setup_infile(pipex);
	setup_outfile(pipex);
	dup2(pipex->fd_infile, STDIN_FILENO);
	dup2(pipex->fd_outfile, STDOUT_FILENO);
	child_process(0, NULL, pipex, envp);
}

void	handle_malloc_error(int *pipes, pid_t *pids)
{
	perror("malloc");
	if (pipes)
		free(pipes);
	if (pids)
		free(pids);
}

void	ft_exec(t_pipex *pipex, char **envp)
{
	int		*pipes;
	pid_t	*pids;

	if (pipex->cmd_count == 1)
		return (handle_single_command(pipex, envp));
	pipes = malloc(sizeof(int) * 2 * (pipex->cmd_count - 1));
	pids = malloc(sizeof(pid_t) * pipex->cmd_count);
	if (!pipes || !pids)
		return (handle_malloc_error(pipes, pids));
	if (!create_pipes(pipes, pipex->cmd_count - 1))
	{
		free(pipes);
		free(pids);
		return ;
	}
	execute_commands(pipex, pipes, pids, envp);
	cleanup_pipes(pipes, pipex->cmd_count - 1);
	wait_for_children(pids, pipex->cmd_count);
	free(pids);
}
