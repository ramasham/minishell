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

// int	handle_heredoc(char *delimiter, t_data *data)
// {
// 	int	pipe_fd[2];
// 	ft_printf("fee qoutes wela la2? %s\n", delimiter);
// 	if (!delimiter)
// 		return (-1);
// 	if (setup_heredoc_pipe(pipe_fd) == -1)
// 		return (-1);
// 	if (read_heredoc_input(pipe_fd, data, delimiter) == -1)
// 	{
// 		close_pipe(pipe_fd);
// 		return (-1);
// 	}
// 	close(pipe_fd[1]);
// 	return (pipe_fd[0]);
// }


int handle_heredoc(char *delimiter, t_data *data)
{
    int pipe_fd[2];
    char *line;
    int expand = 1; // Flag to control expansion

    // Check if the delimiter is quoted
    if (delimiter[0] == '"' || delimiter[0] == '\'')
    {
        char quote = delimiter[0]; // Save the type of quote
        delimiter++; // Skip the opening quote
        delimiter[ft_strlen(delimiter) - 1] = '\0'; // Remove the closing quote
        if (quote == '\'')
            expand = 0; // Disable expansion for single-quoted delimiters
    }

    if (!delimiter)
        return (-1);
    if (pipe(pipe_fd) == -1)
    {
        perror("minishell: pipe");
        return (-1);
    }
    while (1)
    {
        ft_putstr_fd("> ", 1);
        line = get_next_line(STDIN_FILENO);
        if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
        {
            free(line);
            break;
        }
        if (expand)
        {
            // Expand environment variables in the line
            line = expand_heredoc_line(line, data);
        }
        write(pipe_fd[1], line, ft_strlen(line));
        free(line);
    }
    close(pipe_fd[1]);
    return (pipe_fd[0]);
}
