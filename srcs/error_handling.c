/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:36:43 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/01 18:56:15 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_free_memory(char **path, char *path_command)
{
	ft_free_array(path);
	free(path_command);
}

void	ft_cleanup(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count)
	{
		if (pipex->paths_cmds[i])
			free(pipex->paths_cmds[i]);
		if (pipex->args_cmds[i])
			ft_free_array(pipex->args_cmds[i]);
		i++;
	}
	free(pipex->paths_cmds);
	free(pipex->args_cmds);
	if (pipex->fd_infile >= 0)
		close(pipex->fd_infile);
	if (pipex->fd_outfile >= 0)
		close(pipex->fd_outfile);
	unlink(URANDOM_PATH);
}

void	custom_error(char *file, char *message, t_pipex *pipex, int error)
{
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	ft_cleanup(pipex);
	exit(error);
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	ft_error(char *error_message)
{
	ft_putstr_fd(error_message, 2);
	exit(EXIT_FAILURE);
}
