/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:16:41 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/04 16:37:05 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <stdio.h>
# include <time.h>
# include "../libft/libft.h"
# include <stdbool.h>
# include <fcntl.h>

# define URANDOM_PATH ".pipex_urandom"

typedef enum e_args
{
	PROGRAM,
	INFILE,
	CMD1,
	OUTFILE
}	t_args;

typedef enum e_errors
{
	NO_COMAND	= 0,
	NO_FILE	= 2,
	BAD_FD = 9
}	t_errors;

typedef struct s_pipex
{
	int		fd_infile;
	int		fd_outfile;
	char	**paths_cmds;	// Array de paths para todos os comandos
	char	***args_cmds;	// Array de arrays de argumentos
	int		cmd_count;		// Número total de comandos
	char	*input_file;
	char	*output_file;
	char	**commands;	// Array de strings de comandos ("cat", "grep banana")
}	t_pipex;

/*child_process.c*/
void	setup_redirections(int cmd_index, int *pipes, t_pipex *pipex);
void	setup_single_command(t_pipex *pipex);
void	handle_missing_path(t_pipex *pipex, int cmd_index);
void	cleanup_file_descriptors(t_pipex *pipex);
void	child_process(int cmd_index, int *pipes, t_pipex *pipex, char **envp);

/*error_handling.c*/
void	ft_free_memory(char **path, char *path_command);
void	ft_cleanup(t_pipex *pipex);
void	custom_error(char *file, char *message, t_pipex *pipex, int error);
void	ft_free_array(char **path);
int		ft_error(char *error_message);

/*ft_exec_utils.c*/
int		create_pipes(int *pipes, int pipe_count);
void	cleanup_pipes(int *pipes, int pipes_created);
char	**build_command_args(char **argv, int *arg_idx);
// char	*join_arguments(int argc, char **argv);
// char	**split_commands(char *command_line);

//int		count_commands_from_argv(int argc, char **argv);
int		count_commands_from_argv(int argc, char **argv, char *delimiter);
char	**extract_commands_from_argv(int argc, char **argv, char *delimiter);
char	*join_command_args(char **argv, int start, int end);

/*ft_exec.c*/
void	execute_commands(t_pipex *pipex, int *pipes, pid_t *pids, char **envp);
void	wait_for_children(pid_t *pids, int count);
void	handle_single_command(t_pipex *pipex, char **envp);
void	handle_malloc_error(int *pipes, pid_t *pids);
void	ft_exec(t_pipex *pipex, char **envp);

/*ft_split_mod.c*/
char	*get_string(const char *s);
void	clean_words(int words, char **array);
char	**ft_split_mod(char *s);
// int		count_commands(char *command_line);

/*ft_split_utils.c*/
int		ft_countword(const char *input);
int		array_size(char **array);
char	*remove_backslashes(char *s);
char	**remove_scape_symbol(char **s);

/*get_path.c*/
char	*ft_get_path_aux(char **envp);
char	*ft_check_command_location(char *command, char *path_i);
char	*find_path(char *path_aux, char *command);
char	*get_path(char *command, char **envp);

/*handle_urandom.c*/
int		ft_read(char **line, int fd, char limiter);
void	handle_urandom(void);

/*main.c*/
void	check_args(t_pipex *pipex, char **envp);
//void	init_pipex(t_pipex *pipex, int cmd_count, char **argv);

/*parsing_utils.c*/
int		is_only_spaces(const char *str);
void	copy_non_space_strings(char **dest, char **src);
void	remove_spaces(char **array);
char	*is_script(char *cmd);

/*pipex_utils.c*/
void	setup_outfile(t_pipex *pipex);
void	setup_infile(t_pipex *pipex);

/*pipex.c*/
void	ft_execve(char *cmd, char **args, t_pipex *pipex, char **envp);
void	close_all_pipes(int *pipes, int pipe_count);

#endif 