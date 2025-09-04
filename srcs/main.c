/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:42:16 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/04 16:07:39 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// srcs/main.c
#include "../include/pipex.h"

void	check_args(t_pipex *pipex, char **envp)
{
	int	i;
	
	i = 0;
	while (i < pipex->cmd_count)
	{
		// Usa ft_split_mod em cada string de comando
		pipex->args_cmds[i] = ft_split_mod(pipex->commands[i]);
		
		if (pipex->args_cmds[i] && pipex->args_cmds[i][0])
			pipex->paths_cmds[i] = get_path(pipex->args_cmds[i][0], envp);
		else
			pipex->paths_cmds[i] = NULL;
		
		i++;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		i;
	
	if (argc < 4)
	{
		ft_putstr_fd("Usage: ./pipex input.txt cmd1 ! cmd2 ! cmdn output.txt\n", 2);
		exit(1);
	}
	
	// Processa argumentos diretamente com ! como separador
	pipex.commands = extract_commands_from_argv(argc, argv, "!");
	pipex.cmd_count = count_commands_from_argv(argc, argv, "!");
	
	// Arquivos de entrada e saída
	pipex.input_file = argv[1];       // Primeiro argumento após programa
	pipex.output_file = argv[argc - 1]; // Último argumento
	
	// Resto do código permanece igual...
	pipex.paths_cmds = malloc(sizeof(char *) * pipex.cmd_count);
	pipex.args_cmds = malloc(sizeof(char **) * pipex.cmd_count);
	
	if (!pipex.paths_cmds || !pipex.args_cmds)
	{
		perror("malloc");
		exit(1);
	}
	
	i = 0;
	while (i < pipex.cmd_count)
	{
		pipex.paths_cmds[i] = NULL;
		pipex.args_cmds[i] = NULL;
		i++;
	}
	
	pipex.fd_infile = -1;
	pipex.fd_outfile = -1;
	
	check_args(&pipex, envp);
	ft_exec(&pipex, envp);
	ft_cleanup(&pipex);
	
	// Liberar memória dos comandos
	i = 0;
	while (pipex.commands[i])
	{
		free(pipex.commands[i]);
		i++;
	}
	free(pipex.commands);
	
	return (0);
}
