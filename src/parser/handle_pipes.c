/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/02/25 19:05:54 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	free_list_cmd(t_command **node)
{
	t_command	*tmp;

	if (!node || !*node)
		return ;
	while (*node)
	{
		tmp = *node;
		*node = (*node)->next;
		free(tmp->full_cmd);
		free(tmp);
	}
	*node = NULL;
}

void get_command(t_data *node_lst, t_node *current)
{
    t_command   *new_cmd;
    t_node      *temp;
    int         arg_count;

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
            return;
        int i = 0;
        while (current && ft_strcmp(current->content, "|") != 0)
        {
            new_cmd->full_cmd[i] = ft_strdup(current->content);
            if (!new_cmd->full_cmd[i])
                return;
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

