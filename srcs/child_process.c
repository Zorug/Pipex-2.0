/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 21:48:36 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/01 22:00:53 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	setup_redirections(int cmd_index, int *pipes, t_pipex *pipex)
{
	if (cmd_index == 0)
	{
		setup_infile(pipex);
		dup2(pipex->fd_infile, STDIN_FILENO);
		dup2(pipes[1], STDOUT_FILENO);
	}
	else if (cmd_index == pipex->cmd_count - 1)
	{
		setup_outfile(pipex);
		dup2(pipes[2 * (cmd_index - 1)], STDIN_FILENO);
		dup2(pipex->fd_outfile, STDOUT_FILENO);
	}
	else
	{
		dup2(pipes[2 * (cmd_index - 1)], STDIN_FILENO);
		dup2(pipes[2 * cmd_index + 1], STDOUT_FILENO);
	}
	close_all_pipes(pipes, pipex->cmd_count - 1);
}

void	setup_single_command(t_pipex *pipex)
{
	setup_infile(pipex);
	setup_outfile(pipex);
	dup2(pipex->fd_infile, STDIN_FILENO);
	dup2(pipex->fd_outfile, STDOUT_FILENO);
}

void	handle_missing_path(t_pipex *pipex, int cmd_index)
{
	if (pipex->args_cmds[cmd_index] != NULL
		&& pipex->args_cmds[cmd_index][0])
	{
		if (!is_script(pipex->args_cmds[cmd_index][0]))
			pipex->paths_cmds[cmd_index] = ft_strdup(
					pipex->args_cmds[cmd_index][0]);
	}
	else
	{
		ft_cleanup(pipex);
		ft_putstr_fd("command not found\n", 2);
		exit(127);
	}
}

void	cleanup_file_descriptors(t_pipex *pipex)
{
	if (pipex->fd_infile > 0)
		close(pipex->fd_infile);
	if (pipex->fd_outfile > 0)
		close(pipex->fd_outfile);
}

void	child_process(int cmd_index, int *pipes, t_pipex *pipex, char **envp)
{
	if (pipes != NULL)
		setup_redirections(cmd_index, pipes, pipex);
	else
		setup_single_command(pipex);
	if (pipex->paths_cmds[cmd_index] == NULL)
		handle_missing_path(pipex, cmd_index);
	cleanup_file_descriptors(pipex);
	ft_execve(pipex->paths_cmds[cmd_index],
		pipex->args_cmds[cmd_index],
		pipex, envp);
}
