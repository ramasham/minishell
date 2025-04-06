/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:27:57 by laburomm          #+#    #+#             */
/*   Updated: 2025/04/06 16:09:57 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtinn(char *cmd)
{
    return (cmd && (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") ||
            !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") ||
            !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") ||
            !ft_strcmp(cmd, "exit")));
}

void execute_builtins(t_command *command, t_data *data)
{
    if (!command || !command->full_cmd || !command->full_cmd[0])
        return;
    if (!ft_strcmp(command->full_cmd[0], "echo"))
        ft_echo(data, command);
    else if (!ft_strcmp(command->full_cmd[0], "cd"))
        ft_cd(data, command->full_cmd[1]);
    else if (!ft_strcmp(command->full_cmd[0], "pwd"))
        ft_pwd();
    else if (!ft_strcmp(command->full_cmd[0], "export"))
        ft_export(data, command);
    else if (!ft_strcmp(command->full_cmd[0], "unset"))
        ft_unset(data, command);
    else if (!ft_strcmp(command->full_cmd[0], "env"))
        ft_env(data->envp);
    else if (!ft_strcmp(command->full_cmd[0], "exit"))
        ft_exit(command, data);
}

int built_ins(t_command *command, t_data *data)
{
    // int stdin_backup;
    // int stdout_backup;

    // stdin_backup = -1;
    // stdout_backup = -1;
    if (!command || !command->full_cmd || !command->full_cmd[0])
        return (0);
    if (!is_builtinn(command->full_cmd[0]))
        return (0);
    // stdin_backup = dup(STDIN_FILENO);
    // stdout_backup = dup(STDOUT_FILENO);
    // handle_dup2(command, data);
    execute_builtins(command, data);
    // dup2(stdin_backup, STDIN_FILENO);
    // dup2(stdout_backup, STDOUT_FILENO);
    // close(stdin_backup);
    // close(stdout_backup);
    return (1);
}

