/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:49:39 by rsham             #+#    #+#             */
/*   Updated: 2025/02/23 12:24:54 by rsham            ###   ########.fr       */
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
// linked list of commnads
// echo rama | grep luj | wc -l > outfile
void add_argument(char ***cmd_args, char *new_arg)
{
    int len = 0;

    if (*cmd_args)
    {
        while ((*cmd_args)[len])
            len++;
    }

    char **new_cmd = malloc(sizeof(char *) * (len + 2)); // +1 for new arg, +1 for NULL
    if (!new_cmd)
        return;

    for (int i = 0; i < len; i++)
        new_cmd[i] = (*cmd_args)[i];

    new_cmd[len] = strdup(new_arg);
    new_cmd[len + 1] = NULL;

    free(*cmd_args); // Free old array if needed
    *cmd_args = new_cmd;
}


t_command *get_commands(t_node *tokens)
{
    t_command *cmds = NULL;
    t_command *current_cmd = NULL;
    int infile = STDIN_FILENO;
    int outfile = STDOUT_FILENO;

    while (tokens)
    {
        // Handle redirections
        handle_redirections(tokens, &infile, &outfile);

        // Create a new command node if it's the first one or after a pipe
        if (!current_cmd || tokens->type == PIPE)
        {
            if (tokens->type == PIPE)
                tokens = tokens->next; // Move to next token after '|'

            current_cmd = malloc(sizeof(t_command));
            if (!current_cmd)
                return (NULL); // Handle malloc failure
            current_cmd->infile = infile;
            current_cmd->outfile = outfile;
            current_cmd->full_cmd = NULL; // Initialize empty command list
            current_cmd->full_path = NULL; // Will resolve later
            current_cmd->next = NULL;

            // Add the command to the list
            if (!cmds)
                cmds = current_cmd;
            else
            {
                t_command *tmp = cmds;
                while (tmp->next)
                    tmp = tmp->next;
                tmp->next = current_cmd;
            }
        }

        // Collect command arguments
        if (tokens && tokens->type == ARG)
            add_argument(&(current_cmd->full_cmd), tokens->content);

        tokens = tokens->next;
    }

    return cmds;
}


// void    get_cmd(t_data *data, t_node *tokens)
// {
//     int pipe_fd[2];
//     t_command   *new_cmd;
//     t_command *cmd;
//     int infile;
//     int outfile;

//     init_io_file(infile, outfile);
//     cmd = create_new_command(infile, outfile);
//     while (tokens)
//     {
//         if (pipe(pipe_fd) == -1)
//         {
//             ft_putstr_fd("failed\n", 2);
//             return ;
//         }
//         while (tokens->content != PIPE)
//         {
//             cmd->full_cmd = tokens->content;
//             tokens = tokens->next;
//         }
//         if (tokens->content == PIPE)
//             tokens = tokens->next;
//         new_cmd = create_new_command(infile, outfile);
        
        
//     }
// }
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

