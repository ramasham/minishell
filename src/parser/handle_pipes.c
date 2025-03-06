/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/05 20:28:43 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_command(t_data *node_lst, t_node *current)
{
    t_command   *new_cmd;
    int         arg_count;
    int         i;
    t_node      *temp;

    new_cmd = create_new_command();
    if (!new_cmd)
        return;
    while (current)
    {
        arg_count = 0;
        temp = current;
        while (temp && ft_strcmp(temp->content, "|") != 0)
        {
            arg_count++;
            temp = temp->next;
        }
        new_cmd->full_cmd = malloc(sizeof(char *) * (arg_count + 1));
        if (!new_cmd->full_cmd)
        {
            free(new_cmd);
            return;
        }
        i = 0;
        while (current && ft_strcmp(current->content, "|") != 0)
        {
            new_cmd->full_cmd[i] = ft_strdup(current->content);
            if (!new_cmd->full_cmd[i])
            {
                free_full_cmd(new_cmd);
                return;
            }
            current = current->next;
            i++;
        }
        new_cmd->full_cmd[i] = NULL;
        add_command(node_lst, new_cmd);
        if (current && ft_strcmp(current->content, "|") == 0)
            current = current->next;
        new_cmd = create_new_command();
        if (!new_cmd)
            return;
    }
    free_list(node_lst->node);
    // print_command_info(*(node_lst->commands));
}
