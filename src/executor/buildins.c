/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:27:57 by laburomm          #+#    #+#             */
/*   Updated: 2025/03/05 02:02:30 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int built_ins(t_command *command, t_data *data)
{
    if (ft_strcmp(command->full_cmd[0], "echo") == 0)
        ft_echo(command);
    else if (ft_strcmp(command->full_cmd[0], "cd") == 0)
        ft_cd(command->full_cmd[1]);
    else if (ft_strcmp(command->full_cmd[0], "pwd") == 0)
        ft_pwd();
    else if (ft_strcmp(command->full_cmd[0], "export") == 0)
        ft_export(data, command); 
    else if (ft_strcmp(command->full_cmd[0], "unset") == 0)
        ft_unset(data, command); 
    else if (ft_strcmp(command->full_cmd[0], "env") == 0)
        ft_env(data->envp);
    else if (ft_strcmp(command->full_cmd[0], "exit") == 0)
        ft_exit(command, data);
    else
        return (0); // Not a built-in command
    return (1); // Command was a built-in
}