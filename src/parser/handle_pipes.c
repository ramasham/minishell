/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/02/25 13:33:30 by rsham            ###   ########.fr       */
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
    int         arg_count;

    new_cmd = create_new_command();
    if (!new_cmd)
        return;

    while (current)
    {
        arg_count = 0;
        // Count the number of arguments for allocation
        t_node *temp = current;
        while (temp && ft_strcmp(temp->content, "|") != 0)
        {
            arg_count++;
            temp = temp->next;
        }

        // Allocate memory for the command and arguments (+1 for NULL termination)
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
        new_cmd->full_cmd[i] = NULL;  // NULL-terminate the command array

        add_command(node_lst, new_cmd);

        // Move to the next command after the pipe
        if (current && ft_strcmp(current->content, "|") == 0)
            current = current->next;

        new_cmd = create_new_command();
        if (!new_cmd)
            return;
    }

    free_list(node_lst->node);
    print_command_info(*(node_lst->commands));
}


// void get_command(t_data *node_lst, t_node *current)
// {
//     char        *tmp;
//     char        *joined;
//     t_command   *new_cmd;

//     joined = NULL;
//     tmp = NULL;
//     new_cmd = create_new_command();
//     if (!new_cmd)
//         return ;
//     while (current)
//     {
//         while (current && ft_strcmp(current->content, "|") != 0)
//         {
//             if (!new_cmd->full_cmd)
//             {
//                 new_cmd->full_cmd = ft_strdup(current->content);
//                 if (!new_cmd->full_cmd)
//                     return ;
//             }
//             else
//             {
//                 tmp = ft_strjoin(new_cmd->full_cmd, " ");
//                 if (!tmp)
//                     return;
//                 joined = ft_strjoin(tmp, current->content);
//                 if (!joined)
//                 {
//                     free (tmp);
//                     return ;
//                 }
//                 free(tmp);
//                 free(new_cmd->full_cmd);
//                 new_cmd->full_cmd = joined;
//             }
//             if (!new_cmd->full_cmd)
//                 return;
//             current = current->next;
//         }
//         add_command(node_lst, new_cmd);
//         if (current && ft_strcmp(current->content, "|") == 0)
//             current = current->next;
//         new_cmd = create_new_command();
//         if (!new_cmd)
//             return ;
//     }
//     free_list(node_lst->node);
//     // print_command(node_lst);
//     print_command_info(*(node_lst->commands));
//     // free_list_cmd(node_lst->commands);
// }
