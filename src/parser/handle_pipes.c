/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:02:50 by rsham             #+#    #+#             */
/*   Updated: 2025/03/13 16:59:47 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Creates and initializes a new command structure
t_command *create_and_initialize_cmd(void)
{
    t_command *cmd;

    cmd = create_new_command();
    if (!cmd)
        return(NULL);
    cmd->full_cmd = NULL;
    return(cmd);
}

// Counts arguments before a pipe ('|')
int count_args_before_pipe(t_node *current)
{
    int arg_count = 0;

    while (current && ft_strcmp(current->content, "|") != 0)
    {
        arg_count++;
        current = current->next;
    }
    return arg_count;
}

// Fills the command array with arguments before a pipe ('|')
void fill_full_cmd(t_node **current, t_command *new_cmd, int arg_count)
{
    // malloc newcmd  full_cmd
    int i;

    i = 0;
    new_cmd->full_cmd = malloc(sizeof(char *) * (arg_count + 1));
    if (!new_cmd->full_cmd)
    {
        // free_list_cmd(&new_cmd);
        // free_full_cmd(new_cmd);
        return;
    }
    while (*current && ft_strcmp((*current)->content, "|") != 0)
    {
        new_cmd->full_cmd[i] = ft_strdup((*current)->content);
        if (!new_cmd->full_cmd[i])
        {
            free_full_cmd(new_cmd);
            return;
        }
        *current = (*current)->next;
        i++;
    }
    new_cmd->full_cmd[i] = NULL;
}

// Processes the current command by counting args and filling the command array
int process_current_cmd(t_node **current, t_command *new_cmd)
{
    int arg_count;

    arg_count = count_args_before_pipe(*current);
    fill_full_cmd(current, new_cmd, arg_count);
    if (!new_cmd->full_cmd)
        return (-1);
    return (0);
}


// Extracts commands from the node list and adds them to the command list
void get_command(t_data *node_lst, t_node *current)
{
    t_command *new_cmd;

    while (current)
    {
        new_cmd = create_and_initialize_cmd();
        if (!new_cmd)
        {
            free_list_cmd(node_lst->commands);
            return;
        }
        if (process_current_cmd(&current, new_cmd) == -1)
        {
            free_list_cmd(node_lst->commands);
            free(new_cmd);
            return ;
        }
        add_command(node_lst, new_cmd);
        if (current && ft_strcmp(current->content, "|") == 0)
            current = current->next;
    }
    free_list(node_lst->node);
    node_lst->node = NULL;
}
