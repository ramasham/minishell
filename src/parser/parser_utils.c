/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:46:52 by rsham             #+#    #+#             */
/*   Updated: 2025/02/24 18:41:44 by rsham            ###   ########.fr       */
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
void print_command_info(t_command *cmd)
{
    int i = 0;

    printf("----- Command Info -----\n");
    while (cmd)
    {
        printf("Command #%d:\n", i + 1);
        printf("  Infile FD: %d\n", cmd->infile);
        printf("  Outfile FD: %d\n", cmd->outfile);

        if (cmd->full_path)
            printf("  Full Path: %s\n", cmd->full_path);
        else
            printf("  Full Path: (null)\n");

        if (cmd->full_cmd)
        {
            printf("  Command Args: ");
            for (int j = 0; cmd->full_cmd[j]; j++)
                printf("%c", cmd->full_cmd[j]);
            printf("\n");
        }
        else
        {
            printf("  Command Args: (null)\n");
        }

        printf("  Next Command: %s\n", cmd->next ? "Exists" : "NULL");
        printf("------------------------\n");

        cmd = cmd->next;
        i++;
    }
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