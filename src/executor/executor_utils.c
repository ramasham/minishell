/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:36:05 by rsham             #+#    #+#             */
/*   Updated: 2025/04/14 17:40:11 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     count_commands(t_command *cmds)
{
    int i;

    i = 0;
    if (!cmds)
        return (0);
    while (cmds)
    {
        i++;
        cmds = cmds->next;
    }
    return (i);
}


// int check_path(t_data *data)
// {
//     int result;

//     result = get_cmd_path(*data->commands, data);
//     if (result == CMD_NOT_EXECUTABLE) 
//     {
//         data->last_exit_status = CMD_NOT_EXECUTABLE;
//         return (data->last_exit_status);
//     }
//     if (result != 0)
//     {
//         cmd_not_found_msg(*data->commands);
//         data->last_exit_status = CMD_NOT_FOUND;
//         return (data->last_exit_status);
//     }
//     return (0);
// }
