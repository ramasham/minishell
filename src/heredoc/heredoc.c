/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:48:26 by laburomm          #+#    #+#             */
/*   Updated: 2025/03/24 01:40:41 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		exit(130);
	}
}

static void	setup_heredoc_signals(void)
{
	signal(SIGINT, handle_heredoc_signal);
	signal(SIGQUIT, SIG_IGN);
}

// Close both ends of a pipe
void	close_pipe(int pipe_fd[2])
{
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
}

// Set up the pipe for heredoc
int	setup_heredoc_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	return (0);
}

// Process each line of heredoc input
int	process_heredoc_line(char *line, int pipe_fd[2], t_data *data, char *delimiter)
{
	char	*processed_line;

	if (!line)
		return (-1);
	
	// Handle backslashes in heredoc content
	processed_line = handle_backslashes(line);
	if (!processed_line)
		return (-1);

	// Only expand the line if the delimiter is not quoted
	if (!is_quoted_delimiter(delimiter))
	{
		processed_line = expand_heredoc_line(processed_line, data);
		if (!processed_line)
			return (-1);
	}
	
	if (write(pipe_fd[1], processed_line, ft_strlen(processed_line)) == -1)
	{
		perror("minishell: write");
		free(processed_line);
		return (-1);
	}
	free(processed_line);
	return (0);
}

// Read input from the user until the delimiter is found
int	read_heredoc_input(int pipe_fd[2], t_data *data, char *delimiter)
{
	char	*line;
	int		status;

	setup_heredoc_signals();
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(delimiter, 2);
			ft_putstr_fd("')\n", 2);
			break;
		}
		if (process_delimiter(line, delimiter))
		{
			free(line);
			break;
		}
		status = process_heredoc_line(line, pipe_fd, data, delimiter);
		if (status == -1)
		{
			free(line);
			return (-1);
		}
	}
	return (0);
}

int	handle_heredoc(char *delimiter, t_data *data)
{
	int		pipe_fd[2];
	int		status;
	pid_t	pid;

	if (!delimiter)
		return (-1);

	if (setup_heredoc_pipe(pipe_fd) == -1)
		return (-1);

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		close_pipe(pipe_fd);
		return (-1);
	}

	if (pid == 0)
	{
		// Child process
		close(pipe_fd[0]);
		status = read_heredoc_input(pipe_fd, data, delimiter);
		close(pipe_fd[1]);
		exit(status);
	}
	else
	{
		// Parent process
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			close(pipe_fd[0]);
			return (-1);
		}
		return (pipe_fd[0]);
	}
}
