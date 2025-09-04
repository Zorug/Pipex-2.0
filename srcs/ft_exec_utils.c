/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 22:07:54 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/04 16:35:48 by cgross-s         ###   ########.fr       */
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

char	**build_command_args(char **argv, int *arg_idx)
{
	char	**args;
	int		count;
	int		i;
	int		start;

	start = *arg_idx;
	count = 0;
	
	// Conta quantos argumentos até o próximo pipe ou fim
	while (argv[*arg_idx] && ft_strcmp(argv[*arg_idx], "|") != 0)
	{
		count++;
		(*arg_idx)++;
	}
	
	// Aloca array para os argumentos + NULL terminator
	args = malloc((count + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	
	// Copia os argumentos
	i = 0;
	while (i < count)
	{
		args[i] = ft_strdup(argv[start + i]);
		i++;
	}
	args[i] = NULL;
	
	// Avança sobre o pipe (se houver)
	if (argv[*arg_idx] && ft_strcmp(argv[*arg_idx], "|") == 0)
		(*arg_idx)++;
	
	return (args);
}

/*
// srcs/ft_exec_utils.c
char	*join_arguments(int argc, char **argv)
{
	char	*result;
	int		total_length;
	int		i;
	int		pos;
	
	// Calcula tamanho total necessário
	total_length = 0;
	i = 1; // Começa em argv[1] (input.txt)
	while (i < argc - 1) // Para antes do output.txt
	{
		total_length += ft_strlen(argv[i]) + 1; // +1 para espaço
		i++;
	}
	
	result = malloc(total_length + 1);
	if (!result)
		return (NULL);
	
	pos = 0;
	i = 1;
	while (i < argc - 1)
	{
		// Copia cada argumento
		ft_memcpy(result + pos, argv[i], ft_strlen(argv[i]));
		pos += ft_strlen(argv[i]);
		result[pos++] = ' '; // Adiciona espaço entre argumentos
		i++;
	}
	result[pos - 1] = '\0'; // Remove último espaço
	
	return (result);
}

char	**split_commands(char *command_line)
{
	char	**commands;
	int		i;
	int		start;
	int		in_quotes;
	int		cmd_count;
	
	cmd_count = count_commands(command_line);
	commands = malloc((cmd_count + 1) * sizeof(char *));
	if (!commands)
		return (NULL);
	
	i = 0;
	start = 0;
	in_quotes = 0;
	cmd_count = 0;
	
	while (command_line[i])
	{
		if (command_line[i] == '"' || command_line[i] == '\'')
			in_quotes = !in_quotes;
		
		if (command_line[i] == '|' && !in_quotes)
		{
			commands[cmd_count] = ft_strndup(command_line + start, i - start);
			commands[cmd_count] = ft_strtrim(commands[cmd_count], " ");
			cmd_count++;
			start = i + 1;
		}
		i++;
	}
	
	// Último comando
	commands[cmd_count] = ft_strndup(command_line + start, i - start);
	commands[cmd_count] = ft_strtrim(commands[cmd_count], " ");
	commands[cmd_count + 1] = NULL;
	
	return (commands);
}*/

// Conta quantos comandos existem em argv (separados por |)
/*int	count_commands_from_argv(int argc, char **argv)
{
	int	count;
	int	i;
	
	count = 0;
	i = 2; // Começa em argv[2] (primeiro comando)
	
	while (i < argc - 1) // Para antes do output.txt
	{
		if (ft_strcmp(argv[i], "|") == 0)
			count++;
		i++;
	}
	return (count + 1); // +1 para o último comando
}*/

// Conta quantos comandos existem em argv (separados por delimiter)
int	count_commands_from_argv(int argc, char **argv, char *delimiter)
{
	int	count;
	int	i;
	
	count = 1; // Sempre pelo menos 1 comando
	i = 2; // Começa em argv[2] (primeiro comando)
	
	while (i < argc - 1) // Para antes do output.txt
	{
		if (ft_strcmp(argv[i], delimiter) == 0)
			count++;
		i++;
	}
	return (count);
}

/*
// Extrai comandos diretamente de argv
char	**extract_commands_from_argv(int argc, char **argv)
{
	char	**commands;
	int		i;
	int		cmd_index;
	int		start;
	
	commands = malloc((count_commands_from_argv(argc, argv) + 1) * sizeof(char *));
	if (!commands)
		return (NULL);
	
	i = 2;
	cmd_index = 0;
	start = 2;
	
	while (i < argc - 1)
	{
		if (ft_strcmp(argv[i], "|") == 0)
		{
			// Junta os argumentos do comando atual
			commands[cmd_index] = join_command_args(argv, start, i - 1);
			cmd_index++;
			start = i + 1;
		}
		i++;
	}
	
	// Último comando
	commands[cmd_index] = join_command_args(argv, start, argc - 2);
	commands[cmd_index + 1] = NULL;
	
	return (commands);
}*/

// Extrai comandos diretamente de argv usando delimiter
char	**extract_commands_from_argv(int argc, char **argv, char *delimiter)
{
	char	**commands;
	int		i;
	int		cmd_index;
	int		start;
	int		cmd_count;
	
	cmd_count = count_commands_from_argv(argc, argv, delimiter);
	commands = malloc((cmd_count + 1) * sizeof(char *));
	if (!commands)
		return (NULL);
	
	i = 2;
	cmd_index = 0;
	start = 2;
	
	while (i < argc - 1)
	{
		if (ft_strcmp(argv[i], delimiter) == 0)
		{
			commands[cmd_index] = join_command_args(argv, start, i - 1);
			cmd_index++;
			start = i + 1;
		}
		i++;
	}
	
	// Último comando
	commands[cmd_index] = join_command_args(argv, start, argc - 2);
	commands[cmd_index + 1] = NULL;
	
	return (commands);
}

/*
// Junta os argumentos de um comando em uma string
char	*join_command_args(char **argv, int start, int end)
{
	char	*result;
	int		total_length;
	int		i;
	int		pos;
	
	total_length = 0;
	for (i = start; i <= end; i++)
		total_length += ft_strlen(argv[i]) + 1;
	
	result = malloc(total_length + 1);
	if (!result)
		return (NULL);
	
	pos = 0;
	for (i = start; i <= end; i++)
	{
		ft_memcpy(result + pos, argv[i], ft_strlen(argv[i]));
		pos += ft_strlen(argv[i]);
		if (i < end)
			result[pos++] = ' ';
	}
	result[pos] = '\0';
	
	return (result);
}*/

// Junta os argumentos de um comando em uma string
char	*join_command_args(char **argv, int start, int end)
{
	char	*result;
	int		total_length;
	int		i;
	int		pos;
	
	// Calcula tamanho total
	total_length = 0;
	for (i = start; i <= end; i++)
		total_length += ft_strlen(argv[i]) + 1; // +1 para espaço
	
	result = malloc(total_length + 1);
	if (!result)
		return (NULL);
	
	// Concatena os argumentos
	pos = 0;
	for (i = start; i <= end; i++)
	{
		ft_strlcpy(result + pos, argv[i], ft_strlen(argv[i]) + 1);
		pos += ft_strlen(argv[i]);
		if (i < end)
			result[pos++] = ' ';
	}
	result[pos] = '\0';
	
	return (result);
}
