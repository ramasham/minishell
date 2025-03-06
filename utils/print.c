/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:04:28 by rsham             #+#    #+#             */
/*   Updated: 2025/03/06 02:45:57 by rsham            ###   ########.fr       */
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
        printf("token: %s - type: %d\n", head->content, head->type);
        head = head->next;
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

