/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:49:39 by rsham             #+#    #+#             */
/*   Updated: 2025/02/23 19:32:00 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command *create_new_command()
{
    t_command *new_cmd;

    new_cmd = malloc(sizeof(t_command));
    if (!new_cmd)
        return NULL;
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

void get_command(t_data *node_lst, t_node *current)
{
    char        *tmp;
    char        *joined;
    t_command   *new_cmd;

    joined = NULL;
    tmp = NULL;
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
    free_list(node_lst->node);
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
