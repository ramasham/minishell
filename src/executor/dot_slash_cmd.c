/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_slash_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 01:28:42 by rsham             #+#    #+#             */
/*   Updated: 2025/04/09 19:58:10 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_dot_command(t_data *data)
{
    char        *script;
    t_command   *cmd;
    
    cmd = *data->commands;
    script = cmd->full_cmd[1];
    if (!script || access(script, F_OK) != 0)
    {
        ft_putstr_fd(".: filename argument required\n", 2);
        ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
        data->last_exit_status = 1;
        return (1);
    }
    // if (access(script, X_OK) == 0)
    // {
    //     execve(script, cmd->full_cmd + 1, data->envp);
    //     perror("execve failed");
    // }
    // else
    // {
    //     perror("Error: script is not executable");
    //     data->last_exit_status = 1;
    // }
    return (1);
}

int handle_dot_slash_command(t_data *data)
{
    t_command *cmd;
    
    cmd = *data->commands;
    ft_putstr_fd("./: Is a directory\n", 1);
    data->last_exit_status = 1;
    return (data->last_exit_status);
}

void    cmd_error_msg(t_data *data)
{
    ft_putstr_fd("..: command not found\n", 2);
    free_list_cmd(data->commands);
}

int handle_dot_slash_exec(t_data *data)
{
    t_command *cmd;

    cmd = *data->commands;
    if (ft_strcmp(cmd->full_cmd[0], ".") == 0)
    {
        if (handle_dot_command(data))
        {
            free_list_cmd(data->commands);
            return (data->last_exit_status);
        }
    }
    else if ((cmd->full_cmd[0][0] == '.' && cmd->full_cmd[0][1] == '/') && (!cmd->full_cmd[0][2]))
    {
        
        if (handle_dot_slash_command(data))
        {
            free_list_cmd(data->commands);
            return (data->last_exit_status);
        }
    }
    else if (cmd->full_cmd[0][0] == '.' && cmd->full_cmd[0][1] == '.')
    {
        cmd_error_msg(data);
        return (data->last_exit_status);
    }
    return (0);
}
