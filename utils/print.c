/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:04:28 by rsham             #+#    #+#             */
/*   Updated: 2025/04/08 18:38:37 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_command_info(t_command *cmd)
{
    int i = 0;

    printf("----- Command Info -----\n");
    while (cmd)
    {
        printf("Command #%d:\n", i + 1);
        printf("  Infile FD: %d\n", cmd->infile_fd);
        printf("  Outfile FD: %d\n", cmd->outfile_fd);

        if (cmd->full_path)
            printf("  Full Path: %s\n", cmd->full_path);
        else
            printf("  Full Path: (null)\n");

        if (cmd->full_cmd)
        {
            printf("  Command Args: ");
            for (int j = 0; cmd->full_cmd[j]; j++)
                printf("%s ", cmd->full_cmd[j]);
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

void    print_list(t_node *head)
{
    while (head)
    {
        printf("token: %s\n", head->content);
        head = head->next;
    }
}

// void print_command(t_data *newcmd)
// {
//     int i = 0;
//     if (!newcmd || !newcmd->commands)
//         return;

//     t_command *current = *newcmd->commands;
//     while (current)
//     {
//         ft_printf("%d: command is %s \n", i, current->full_cmd);
//         current = current->next;
//         i++;
//     }
// }

void print_command(t_data *newcmd)
{
    int i = 0;

    if (!newcmd || !newcmd->commands)
        return;

    t_command *current = *newcmd->commands;
    while (current)
    {
        ft_printf("%d: command is ", i);
        if (current->full_cmd) // Ensure full_cmd is not NULL
        {
            int j = 0;
            while (current->full_cmd[j]) // Iterate over the array of strings
            {
                ft_printf("%s ", current->full_cmd[j]);
                j++;
            }
        }
        ft_printf("\n");
        current = current->next;
        i++;
    }
}


