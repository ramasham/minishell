/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:46:52 by rsham             #+#    #+#             */
/*   Updated: 2025/02/25 19:04:48 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command *create_new_command()
{
    t_command *new_cmd;

    new_cmd = malloc(sizeof(t_command));
    if (!new_cmd)
        return NULL;
    new_cmd->infile = STDIN_FILENO;
    new_cmd->outfile = STDOUT_FILENO;
    new_cmd->full_cmd = NULL;
    new_cmd->full_path = NULL;
    new_cmd->next = NULL;
    return (new_cmd);
}



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
    tmp = data->commands;
    if (!*tmp)
        *tmp = new_cmd;
    else
    {
        while ((*tmp)->next)
            tmp = &(*tmp)->next;
        (*tmp)->next = new_cmd;
    }
}

// static void print_node_list(t_node *node)
// {
//     int i = 0;
//     while (node)
//     {
//         ft_printf("Node %d: content = %s\n", i, node->content);  // Print the content of each node
//         node = node->next;  // Move to the next node in the list
//         i++;
//     }
// }