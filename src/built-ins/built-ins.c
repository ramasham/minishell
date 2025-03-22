/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:27:57 by laburomm          #+#    #+#             */
/*   Updated: 2025/03/22 23:39:13 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int built_ins(t_command *command, t_data *data)
{
    int stdin_backup = -1;
    int stdout_backup = -1;

    if (!command || !command->full_cmd || !command->full_cmd[0])
        return (0);

    // If it's a built-in command, apply redirection
    if (ft_strcmp(command->full_cmd[0], "echo") == 0 || 
        ft_strcmp(command->full_cmd[0], "cd") == 0 ||
        ft_strcmp(command->full_cmd[0], "pwd") == 0 ||
        ft_strcmp(command->full_cmd[0], "export") == 0 ||
        ft_strcmp(command->full_cmd[0], "unset") == 0 ||
        ft_strcmp(command->full_cmd[0], "env") == 0 ||
        ft_strcmp(command->full_cmd[0], "exit") == 0)
    {
        // Backup original stdin and stdout before redirecting
        stdin_backup = dup(STDIN_FILENO);
        stdout_backup = dup(STDOUT_FILENO);
        
        // Apply redirection for the built-in command
        set_redi(command, data);
    }

    // Execute the built-in command
    if (ft_strcmp(command->full_cmd[0], "echo") == 0)
        ft_echo(command);
    else if (ft_strcmp(command->full_cmd[0], "cd") == 0)
        ft_cd(data, command->full_cmd[1]);
    else if (ft_strcmp(command->full_cmd[0], "pwd") == 0)
        ft_pwd();
    else if (ft_strcmp(command->full_cmd[0], "export") == 0)
        ft_export(data, command);
    else if (ft_strcmp(command->full_cmd[0], "unset") == 0)
        ft_unset(data, command);
    else if (ft_strcmp(command->full_cmd[0], "env") == 0)
        ft_env(data->envp);
    else if (ft_strcmp(command->full_cmd[0], "exit") == 0)
    {
        ft_exit(command, data);
        return (1);
    }
    else
        return (0);

    // Restore original stdin and stdout after built-in command execution
    if (stdin_backup != -1)
    {
        dup2(stdin_backup, STDIN_FILENO);
        dup2(stdout_backup, STDOUT_FILENO);
        close(stdin_backup);
        close(stdout_backup);
    }

    data->last_exit_status = 0;
    return (1);
}

