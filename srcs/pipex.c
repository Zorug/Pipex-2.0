/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:22:01 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/02 20:49:38 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_execve(char *cmd, char **args, t_pipex *pipex, char **envp)
{
	if (execve(cmd, args, envp) == -1)
	{
		if (access(cmd, X_OK) == -1)
		{
			if (access(cmd, F_OK) == -1)
			{
				if (args[0][0] == '/' || is_script(args[0]))
					custom_error(args[0],
						"No such file or directory", pipex, 127);
				custom_error(args[0],
					"command not found", pipex, 127);
			}
			perror(args[0]);
			ft_cleanup(pipex);
			exit(126);
		}
	}
}

// Função para fechar todos os pipes
void	close_all_pipes(int *pipes, int pipe_count)
{
	int	i;

	if (pipes == NULL)
		return ;
	i = 0;
	while (i < 2 * pipe_count)
	{
		close(pipes[i]);
		i++;
	}
}
