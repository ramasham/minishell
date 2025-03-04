/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 02:06:43 by laburomm          #+#    #+#             */
/*   Updated: 2025/03/05 02:09:40 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void remove_env_var(t_data *data, char *var)
{
    int j = 0;

    while (data->envp[j])
    {
        if (ft_strncmp(data->envp[j], var, ft_strlen(var)) == 0
            && data->envp[j][ft_strlen(var)] == '=')
        {
            free(data->envp[j]);
            // Shift the remaining elements
            while (data->envp[j])
            {
                data->envp[j] = data->envp[j + 1];
                j++;
            }
            break;
        }
        j++;
    }
}

void ft_unset(t_data *data, t_command *command)
{
    int i = 1;

    if (!command->full_cmd[1])
        return;

    while (command->full_cmd[i])
    {
        remove_env_var(data, command->full_cmd[i]);
        i++;
    }
}

void ft_echo(t_command *command)
{
    int i = 1;
    int newline = 1;

    // Check for -n option
    if (command->full_cmd[1] && ft_strcmp(command->full_cmd[1], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    // Print the rest of the arguments
    while (command->full_cmd[i])
    {
        write(1, command->full_cmd[i], ft_strlen(command->full_cmd[i]));
        if (command->full_cmd[i + 1])
            write(1, " ", 1);
        i++;
    }

    // Print newline if -n is not set
    if (newline)
        write(1, "\n", 1);
}