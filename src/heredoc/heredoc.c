/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:48:26 by laburomm          #+#    #+#             */
/*   Updated: 2025/04/06 19:30:36 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// tokenize the input
// detect <<
// take the next token as delim 
// mark if the delim is quoted or not 

// handle heredoc input before forking
// create a pipe 
// prompt the user > until a delim is found
// if (unquoted) -> pass the line to expander
// else -> skip expansion
// write the (possibly expanded) line into the pipe, followed by a newline
// repeat until delimiter is matched
// close the write-end of the pipe
// store the read-end fd in the command struct (cmd->heredoc_fd)

int handle_heredoc(t_command *cmd)
{
    int     pipe_fd[2];
    char    *line;
    // char    *newline;
    
    if (pipe(pipe_fd) == -1)
        return (-1);
    // printf("delim = %s\n", cmd->heredoc_delim);
    // printf("is q = %d\n", cmd->quoted);
    while (1)
    {
        ft_putstr_fd("> ", 1);
        line = get_next_line(STDIN_FILENO);
        if (!line)
            break;
        // if (cmd->quoted)
        //     heredoc_expander(line);
        if (cmd->heredoc_delim && ft_strncmp(line, cmd->heredoc_delim, ft_strlen(cmd->heredoc_delim)) == 0)
        {
            free(line);
            break;
        }
        write(pipe_fd[1], line, ft_strlen(line));
        free(line);
    }
    close(pipe_fd[1]);
    return (0);
}

