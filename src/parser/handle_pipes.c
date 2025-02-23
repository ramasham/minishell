/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:49:39 by rsham             #+#    #+#             */
/*   Updated: 2025/02/23 17:21:51 by rsham            ###   ########.fr       */
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
t_command *create_new_command()
{
    t_command *new_cmd = malloc(sizeof(t_command));
    if (!new_cmd)
        return NULL;

    // new_cmd->infile = infile;
    // new_cmd->outfile = outfile;
    new_cmd->full_cmd = NULL;
    new_cmd->full_path = NULL;
    new_cmd->next = NULL;
    return new_cmd;
}
//initialize in/out files
// void    init_io_file(int infile, int outfile)
// {
//     infile = STDIN_FILENO;
//     outfile = STDOUT_FILENO;
// }

// To print the new commands
void print_command(t_data *newcmd)
{
    int i = 0;
    if (!newcmd || !newcmd->commands)
        return;

    t_command *current = *newcmd->commands;
    while (current)
    {
        ft_printf("%d: command is %s\n", i, current->full_cmd);
        current = current->next;
        i++;
    }
}

void get_command(t_data *node_lst, t_node *current)
{
    t_command   *new_cmd;
    char        *tmp;
    char        *joined;

    new_cmd = create_new_command();
    if (!new_cmd)
        return ;
    while (current)
    {
        while (current && ft_strcmp(current->content, "|") != 0)
        {
            if (!new_cmd->full_cmd)
            {
                new_cmd->full_cmd = ft_strdup(current->content);
                if (!new_cmd->full_cmd)
                    return ;
            }
            else
            {
                tmp = ft_strjoin(new_cmd->full_cmd, " ");
                if (!tmp)
                    return;
                joined = ft_strjoin(tmp, current->content);
                if (!joined)
                {
                    free (tmp);
                    return ;
                }
                free(tmp);
                free(new_cmd->full_cmd);
                new_cmd->full_cmd = joined;
            }
            if (!new_cmd->full_cmd)
                return;
            current = current->next;
        }
        add_command(node_lst, new_cmd);
        if (current && ft_strcmp(current->content, "|") == 0)
            current = current->next;
        new_cmd = create_new_command();
        if (!new_cmd)
            return ;
    }
    print_command(node_lst);
}


void add_command(t_data *data, t_command *new_cmd)
{
    t_command **tmp;

    if (!data->commands)
    {
        data->commands = malloc(sizeof(t_command *));
        if (!data->commands)
            return;
        *data->commands = NULL;
    }
    if (!*data->commands)
        *data->commands = new_cmd;
    else
    {
        tmp = data->commands;
        while ((*tmp)->next)
            tmp = &(*tmp)->next;
        (*tmp)->next = new_cmd;
    }
}
