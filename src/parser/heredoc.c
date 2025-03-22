/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:48:26 by laburomm          #+#    #+#             */
/*   Updated: 2025/03/22 23:45:24 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		perror("pipe");
		return (-1);
	}
	return (0);
}

// Process each line of heredoc input
int process_heredoc_line(char *line, int pipe_fd[2], t_data *data, char *delimiter)
{
    if (!line)
        return (-1);
    // Only expand the line if the delimiter is not quoted
    if (!is_quoted_delimiter(delimiter))
    {
        line = expand_heredoc_line(line, data);
        if (!line)
            return (-1);
    }
    write_heredoc_to_pipe(line, pipe_fd);
    return (0);
}

// Read input from the user until the delimiter is found
int	read_heredoc_input(int pipe_fd[2], t_data *data, char *delimiter)
{
	char	*line;

	printf("del 2 %s:\n", delimiter);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line || process_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		if (process_heredoc_line(line, pipe_fd, data, delimiter) == -1)
			return (-1);
		
	}
	return (0);
}

int	handle_heredoc(char *delimiter, t_data *data)
{
	int	pipe_fd[2];
	
	if (!delimiter)
		return (-1);
	if (setup_heredoc_pipe(pipe_fd) == -1)
		return (-1);
	if (read_heredoc_input(pipe_fd, data, delimiter) == -1)
	{
		close_pipe(pipe_fd);
		return (-1);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}