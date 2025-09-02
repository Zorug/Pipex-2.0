/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 22:07:54 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/01 22:08:28 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	create_pipes(int *pipes, int pipe_count)
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
}
