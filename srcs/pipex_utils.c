/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:30:09 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/02 22:57:19 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	setup_outfile(t_pipex *pipex)
{
	pipex->fd_outfile = open(pipex->output_file,
			O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (pipex->fd_outfile == -1)
	{
		perror(pipex->output_file);
		ft_cleanup(pipex);
		if (open(pipex->output_file, O_WRONLY) != 0)
			exit(2);
		exit(1);
	}
}

void	setup_infile(t_pipex *pipex)
{
	if (ft_strncmp(pipex->input_file, "/dev/urandom", 12) == 0)
	{
		handle_urandom();
		pipex->fd_infile = open(URANDOM_PATH, O_RDONLY);
	}
	else
		pipex->fd_infile = open(pipex->input_file, O_RDONLY, 0444);
	if (pipex->fd_infile == -1)
	{
		perror(pipex->input_file);
		ft_cleanup(pipex);
		exit(1);
	}
}
