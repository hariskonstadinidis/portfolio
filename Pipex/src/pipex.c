/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 13:42:13 by hariskon          #+#    #+#             */
/*   Updated: 2025/11/19 18:14:50 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/// @brief Opens an input or output file with the appropriate mode.
/// @details For input files, the function opens the file in read-only mode.
///          For output files, it creates/truncates the file with write-only
///          permissions (0644). On failure, the function prints a descriptive
///          error message using perror() so the caller can decide how to
///          handle the error.
/// @param filename Path to the file to be opened.
/// @param in_out Selector indicating input (IN) or output (OUT) mode.
/// @return The file descriptor on success, or -1 if the open() call fails.
static int	file_open(char *filename, enum e_in_out in_out)
{
	int	fd;

	fd = -1;
	if (in_out == IN)
		fd = open(filename, O_RDONLY);
	else if (in_out == OUT)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(filename);
		fd = open("/dev/null", O_RDONLY);
		if (fd == -1)
			return (perror("Failed to open /dev/null"), -1);
	}
	return (fd);
}

/// @brief Executes a single pipeline command in the child process.
/// @details Sets up the child's file descriptors by redirecting the current
///          input source to STDIN, redirecting the pipe's write end to STDOUT,
///          and closing all unused FDs. If any redirection fails, the child
///          prints an appropriate error and exits immediately. On success,
///          the function replaces the child process image with the command
///          specified in data->cmds[i] using execve(). If execve() fails,
///          control passes to child_exec_error() for error reporting and
///          cleanup.
/// @param data Pointer to the program’s main state structure.
/// @param i Index of the command to execute within the parsed command list.
static void	child_proccess(t_data *data, int i)
{
	if (dup2(data->input_fd, STDIN_FILENO) == -1)
		(perror("Dup2 for STDIN failed"), _exit(EXIT_FAILURE));
	close(data->input_fd);
	if (dup2(data->pipefd[1], STDOUT_FILENO) == -1)
		(perror("Dup2 for STDOUT failed"), _exit(EXIT_FAILURE));
	close(data->pipefd[1]);
	close(data->pipefd[0]);
	execve(data->cmds[i][0], data->cmds[i], data->envp);
	child_exec_error(data, i);
}

/// @brief Executes all pipeline commands except the final one.
/// @details Iterates through each intermediate command, creating a pipe for
///          each stage, forking a child to execute the command, and preparing
///          the read end of the pipe as the input for the next iteration.
///          In the parent process, the previous input file descriptor is
///          closed, the write end of the pipe is closed, and the read end
///          becomes the new input source. Child PIDs are stored for later
///          waiting.
/// @param data Pointer to the program’s main state structure.
/// @return 1 on success, or 0 if a pipe or fork operation fails.
static int	execute_loop(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data->cmds_count) - 1)
	{
		if (pipe(data->pipefd) < 0)
			return (close(data->input_fd), perror("Pipe Failed"), 0);
		data->pids[i] = fork();
		if (data->pids[i] < 0)
			return (perror("Fork failed"), 0);
		else if (data->pids[i] == 0)
			child_proccess(data, i);
		else
		{
			if (data->input_fd != -1)
				close(data->input_fd);
			close(data->pipefd[1]);
			data->input_fd = data->pipefd[0];
		}
		i++;
	}
	return (1);
}

/// @brief Executes the final command in the pipeline.
/// @details Opens the output file in truncate mode, forks a child to run the
///          last command, and closes the pipe file descriptors in the parent.
///          The child's PID is stored for later synchronization via wait().
/// @param data Pointer to the program's main state structure.
/// @return 1 on success, 0 if file opening or forking fails.
static int	execute_last(t_data *data)
{
	int	last_cmd;

	last_cmd = data->cmds_count - 1;
	close(data->pipefd[1]);
	data->pipefd[1] = file_open(data->argv[data->argc - 1], OUT);
	if (data->pipefd[1] == -1)
		return (0);
	data->pids[data->cmds_count - 1] = fork();
	if (data->pids[data->cmds_count - 1] < 0)
		return (perror("Fork failed"), 0);
	else if (data->pids[data->cmds_count - 1] == 0)
		child_proccess(data, last_cmd);
	else
		close_pipefd(data->pipefd);
	return (1);
}

/// @brief Entry point for the mandatory pipex program.
/// @details Validates arguments, initializes internal state, opens the
///          input file, executes the pipeline commands in order, waits for
///          all child processes to finish, and frees all allocated resources
///          before exiting.
/// @param argc Number of command-line arguments.
/// @param argv Argument vector: infile, cmd1, cmd2, outfile.
/// @param envp Environment variables passed to the program.
/// @return 0 on success, 1 if initialization or execution fails.
int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 5)
		return (write(2, "Wrong input, put 4 arguments\n", 29), 1);
	data = setup(argc, argv, envp);
	if (!data)
		return (1);
	data->input_fd = file_open(argv[1], IN);
	if (data->input_fd == -1)
		return (free_data(data), 1);
	if (!execute_loop(data))
		return (pid_wait_and_free(data));
	if (!execute_last(data))
		return (pid_wait_and_free(data));
	return (pid_wait_and_free(data));
}
