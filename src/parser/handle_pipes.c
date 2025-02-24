/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/02/24 11:09:52 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

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
