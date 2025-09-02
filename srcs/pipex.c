/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:22:01 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/01 21:56:06 by cgross-s         ###   ########.fr       */
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
// for (i = 0; i < 2 * pipe_count; i++)
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
/*
// Configurar redirecionamentos apenas se houver pipes
void	child_process(int cmd_index, int *pipes, t_pipex *pipex, char **envp)
{
	if (pipes != NULL)
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
	else
	{
		setup_infile(pipex);
		setup_outfile(pipex);
		dup2(pipex->fd_infile, STDIN_FILENO);
		dup2(pipex->fd_outfile, STDOUT_FILENO);
	}
	if (pipex->paths_cmds[cmd_index] == NULL)
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
	if (pipex->fd_infile > 0)
		close(pipex->fd_infile);
	if (pipex->fd_outfile > 0)
		close(pipex->fd_outfile);
	ft_execve(pipex->paths_cmds[cmd_index],
		pipex->args_cmds[cmd_index],
		pipex, envp);
}
*/

/*
void	ft_exec(t_pipex *pipex, char **envp)
{
	int     i;
	int     *pipes;
	pid_t   *pids;
	int     status;
	
	if (pipex->cmd_count == 1)
	{
		setup_infile(pipex);
		setup_outfile(pipex);
		dup2(pipex->fd_infile, STDIN_FILENO);
		dup2(pipex->fd_outfile, STDOUT_FILENO);
		child_process(0, NULL, pipex, envp);
		return;
	}
	pipes = malloc(sizeof(int) * 2 * (pipex->cmd_count - 1));
	pids = malloc(sizeof(pid_t) * pipex->cmd_count);
	if (!pipes || !pids)
	{
		perror("malloc");
		if (pipes) free(pipes);
		if (pids) free(pids);
		return;
	}
	for (i = 0; i < pipex->cmd_count - 1; i++)
	{
		if (pipe(pipes + i * 2) == -1)
		{
			perror("pipe");
			for (int j = 0; j < i * 2; j++)
				close(pipes[j]);
			free(pipes);
			free(pids);
			return;
		}
	}
	for (i = 0; i < pipex->cmd_count; i++)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			continue;
		}
		if (pids[i] == 0)
		{
			child_process(i, pipes, pipex, envp);
		}
	}
	for (i = 0; i < 2 * (pipex->cmd_count - 1); i++)
		close(pipes[i]);
	for (i = 0; i < pipex->cmd_count; i++)
	{
		if (pids[i] > 0)
			waitpid(pids[i], &status, 0);
	}
	free(pipes);
	free(pids);
} */

/*
// Em srcs/pipex.c
void ft_exec(t_pipex *pipex, char **envp)
{
    int     i;
    int     *pipes;
    pid_t   *pids;
    int     status;
    
    if (pipex->cmd_count == 1)
    {
        setup_infile(pipex);
        setup_outfile(pipex);
        dup2(pipex->fd_infile, STDIN_FILENO);
        dup2(pipex->fd_outfile, STDOUT_FILENO);
        child_process(0, NULL, pipex, envp);
        return;
    }
    
    pipes = malloc(sizeof(int) * 2 * (pipex->cmd_count - 1));
    pids = malloc(sizeof(pid_t) * pipex->cmd_count);
    
    if (!pipes || !pids)
    {
        perror("malloc");
        if (pipes) free(pipes);
        if (pids) free(pids);
        return;
    }
    
    // Criar pipes
    for (i = 0; i < pipex->cmd_count - 1; i++)
    {
        if (pipe(pipes + i * 2) == -1)
        {
            perror("pipe");
            // Fechar pipes já criados
            for (int j = 0; j < i * 2; j++)
                close(pipes[j]);
            free(pipes);
            free(pids);
            return;
        }
    }
    
    // Criar processos filhos
    for (i = 0; i < pipex->cmd_count; i++)
    {
        pids[i] = fork();
        if (pids[i] == -1)
        {
            perror("fork");
            continue;
        }
        
        if (pids[i] == 0)
        {
            child_process(i, pipes, pipex, envp);
            exit(EXIT_FAILURE); // Nunca deveria chegar aqui
        }
    }
    
    // Fechar todos os pipes no processo pai
    for (i = 0; i < 2 * (pipex->cmd_count - 1); i++)
        close(pipes[i]);
    
    // Esperar por todos os processos filhos (BLOCKING)
    for (i = 0; i < pipex->cmd_count; i++)
    {
        if (pids[i] > 0)
        {
            waitpid(pids[i], &status, 0); // 0 = blocking
            // Verificar se o processo filho terminou normalmente
            if (WIFEXITED(status))
            {
                // Opcional: tratar exit codes diferentes
            }
        }
    }
    
    free(pipes);
    free(pids);
}*/
