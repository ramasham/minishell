/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:27:57 by laburomm          #+#    #+#             */
/*   Updated: 2025/02/26 17:36:27 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int executer(t_command *cmd, char **envp)
{
    //if built_ins
    //built_ins
    //if not
    //external_exec.
    //if not 
    //pipe
    //if not 
    //rediection
    
}
int built_ins(t_command *command, char **env)
{
    if (!command || !command->full_cmd || !command->full_cmd[0])
        return (0);  // No command given
    if (strcmp(command->full_cmd[0], "echo") == 0)
        ft_echo(command->full_cmd);
    else if (strcmp(command->full_cmd[0], "pwd") == 0)
        ft_pwd();
    else if (strcmp(command->full_cmd[0], "cd") == 0)
        ft_cd(command->full_cmd[1]);  // Pass directory argument
    else if (strcmp(command->full_cmd[0], "export") == 0)
        ft_export(command->full_cmd[0]);  // Pass key=value
    else if (strcmp(command->full_cmd[0], "unset") == 0)
        ft_unset(command->full_cmd[1]);  // Pass key
    else if (strcmp(command->full_cmd[0], "exit") == 0)
        ft_exit();
    else if (strcmp(command->full_cmd[0], "env") == 0)
        ft_env(env);
    else
        return (0);// if failure == external 
    return (1);// if success
}
