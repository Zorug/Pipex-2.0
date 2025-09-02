/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:42:16 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/01 19:43:17 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	check_args(t_pipex *pipex, char **envp)
{
	int	i;
	int	cmd_index;

	i = 0;
	while (i < pipex->cmd_count)
	{
		cmd_index = CMD1 + i;
		if (pipex->argv[cmd_index][0] == '\0')
		{
			pipex->args_cmds[i] = NULL;
			pipex->paths_cmds[i] = NULL;
		}
		else
		{
			pipex->args_cmds[i] = ft_split_mod(pipex->argv[cmd_index]);
			if (pipex->args_cmds[i] && pipex->args_cmds[i][0])
				pipex->paths_cmds[i] = get_path(pipex->args_cmds[i][0], envp);
			else
				pipex->paths_cmds[i] = NULL;
		}
		i++;
	}
}

void	init_pipex(t_pipex *pipex, int cmd_count, char **argv)
{
	int	i;

	pipex->cmd_count = cmd_count;
	pipex->paths_cmds = malloc(sizeof(char *) * cmd_count);
	pipex->args_cmds = malloc(sizeof(char **) * cmd_count);
	pipex->argv = argv;
	i = 0;
	while (i < cmd_count)
	{
		pipex->paths_cmds[i] = NULL;
		pipex->args_cmds[i] = NULL;
		i++;
	}
	pipex->fd_infile = -1;
	pipex->fd_outfile = -1;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
		ft_error("Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2\n");
	init_pipex(&pipex, argc - 3, argv);
	check_args(&pipex, envp);
	ft_exec(&pipex, envp);
	ft_cleanup(&pipex);
	return (0);
}

/*
echo -e "banana\nlaranja\nbanana\nuva\nabacaxi\nbanana" > input.txt

valgrind --leak-check=full --show-leak-kinds=all --track-fds=
yes --trace-children=yes ./pipex

./pipex input.txt "grep banana" "wc -l" output.txt
< input.txt grep banana | wc -l > output.txt

# Teste com 4 comandos
./pipex input.txt "cat" "grep banana" "sort" "uniq" output3.txt

./pipex input.txt "cat -e" "wc -l" outfile.txt
./pipex input.txt "cat" "echo" output.txt
./pipex input.txt "tr a-z A-Z" "rev" output.txt

./pipex input.txt "cat -e" "cut -d\$ -f1" output.txt | JP error
./pipex input.txt "grep ^b" "sort -r" output.txt

./pipex input.txt "banana123" "wc -l" output.txt
# Esperado: erro de "command not found" e exit code 127

./pipex nofile.txt "cat" "wc -l" output.txt
# Esperado: erro de "No such file or directory"

touch secret.txt && chmod 000 secret.txt
./pipex secret.txt "cat" "wc -l" output.txt
# Esperado: "Permission denied"

./pipex input.txt "grep nadaencontrado" "wc -l" output.txt
# Esperado: output.txt deve conter 0

SCRIPT .SH
echo -e '#!/bin/bash\necho "olá do script!"' > test.sh
chmod +x test.sh
./pipex input.txt "./test.sh" "wc -l" output.txt

./pipex input.txt "awk '{print $1}'" "sort" output.txt
./pipex input.txt "sed 's/banana/laranja/g'" "tee log.txt" output.txt

URANDOM
./pipex /dev/urandom "head -c 100" "wc -c" output.txt

Comparação automática com shell (bash vs pipex)
< input.txt grep banana | wc -l > expected.txt
./pipex input.txt "grep banana" "wc -l" actual.txt
diff expected.txt actual.txt && echo "✅ OK" || echo "❌ Diferente"

*/