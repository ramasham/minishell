/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:49:24 by rsham             #+#    #+#             */
/*   Updated: 2025/02/23 17:24:13 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handle redirection 
// in t_node , check for redirection and fds
//after that create t_command struct
// and intialize it 
// then each command is added to t_command linked
//list for execution 

//handle redirection :
// if (>) ,(>>) found -> handle_output_redirection
// handle_output_redirection ->
// open the file(next token), set outfile to fd of the opened file
// if (<) -> handle_input_redirection
// handle_input_redirection ->
//  open the file(next token), set infile to fd of the opened file
// if (>>) found -> handle heredoc redirection
// Create a pipe and set infile to the pipe's read end ->
// Continuously read input until the delimiter
// is encountered, and then close the pipe.


void    handle_redirections(t_node *current, int *infile, int *outfile)
{
    while (current)
    {
        if (ft_strcmp(current->content, REDIR_OUT1) == 0 || ft_strcmp(current->content, APPEND1) == 0)
            *outfile = handle_output_redirection(current->content, current->next->content);
        else if (ft_strcmp(current->content, REDIR_IN1) == 0)
            *infile = handle_input_redirection(current->next->content);
        // else if (ft_strcmp(current->content, HERE_DOC1) == 0)
        //     *infile = handle_heredoc(current->next->content);
        current = current->next;
    }
}

int handle_output_redirection(char *operator, char *filename)
{
    int fd;

    if (ft_strcmp(operator, REDIR_OUT1) == 0)
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644 );
    else if (ft_strcmp(operator, APPEND1) == 0)
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644 );
    else
        return (-1);
    if (fd == -1)
        perror("Output redirection failed");
    return (fd);
}

int handle_input_redirection(char  *filename)
{
    int fd;
    
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Input redirection failed");
    }
    return (fd);
}