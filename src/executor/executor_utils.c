/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:36:05 by rsham             #+#    #+#             */
/*   Updated: 2025/03/11 20:04:34 by rsham            ###   ########.fr       */
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

int     is_external(t_command *cmd, t_data *data)
{
    if (get_cmd_path(cmd, data) == 0)
        return (1);
    else
        return (0);
}

int is_redirection(t_command *cmd)
{
    int i;

    i = 0;
    while (cmd->full_cmd[i])
    {
        if (ft_strcmp(cmd->full_cmd[i], ">") == 0)
            return (1);
        else if (ft_strcmp(cmd->full_cmd[i], "<") == 0)
            return (1);
        i++;
    }
    return (0);
}

int     validate_cmd(t_data *data, t_command *cmds)
{
    if (get_cmd_path(cmds, data))
    {
        cmd_not_found_msg(cmds);
        data->last_exit_status = CMD_NOT_FOUND;
        return (data->last_exit_status);
    }
    if (!cmds->full_path)
    {
        data->last_exit_status = 1;
        return (data->last_exit_status);
    }
    if (access(cmds->full_path, F_OK) == -1)
    {
        perror(cmds->full_path);
        data->last_exit_status = CMD_NOT_FOUND;
        // exit(data->last_exit_status);
        return (data->last_exit_status);
    }
    if (access(cmds->full_path, X_OK) == -1)
    {
        ft_putstr_fd(": Permission denied\n", 2);
        data->last_exit_status = CMD_NOT_EXECUTABLE;
        // exit(data->last_exit_status);
        return (data->last_exit_status);
    }
    return (0);
}
