/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:48:26 by laburomm          #+#    #+#             */
/*   Updated: 2025/04/06 02:21:15 by rsham            ###   ########.fr       */
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

int handle_heredoc(char *delim, t_data *data)
{
    int pipe[2];
    
    while (1)
    {
        ft_putchar_fd("> ", 1);
        
    }
}