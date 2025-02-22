/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:49:39 by rsham             #+#    #+#             */
/*   Updated: 2025/02/22 21:49:14 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// handle pipe process
// if (|) -> create a pipe
// pipe_fd[0]: Read end → Connects to the next command’s infile.
// pipe_fd[1]: Write end → Connects to the current command’s outfile.
// assign fds
// set outfile -> pipe_fd[1]
// set infile -> pipe_fd[0]

#include <stdio.h>

// Create and initialize a new command node
t_command *create_new_command(int infile, int outfile)
{
    t_command *new_cmd = malloc(sizeof(t_command));
    if (!new_cmd)
        return NULL;

    new_cmd->infile = infile;
    new_cmd->outfile = outfile;
    new_cmd->full_cmd = NULL;
    new_cmd->full_path = NULL;
    new_cmd->next = NULL;
    return new_cmd;
}
void    init_io_file(int infile, int outfile)
{
    infile = STDIN_FILENO;
    outfile = STDOUT_FILENO;
}
void    get_cmd(t_data *data, t_node *tokens)
{
    int infile;
    int outfile;
    t_command   *curr_cmd;

    curr_cmd = NULL;
    init_io_file(infile, outfile);
    while (tokens)
    {
        
    }
}
void add_command(t_data *data, t_command *new_cmd)
{
    if (!data->commands)
        data->commands = new_cmd;
    else
    {
        t_command *tmp = data->commands;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_cmd;
    }
}

