/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 02:06:43 by laburomm          #+#    #+#             */
/*   Updated: 2025/03/08 01:49:54 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void remove_env_var(t_data *data, char *var)
{
    int j;

    j = 0;
    while (data->envp[j])
    {
        if (ft_strncmp(data->envp[j], var, ft_strlen(var)) == 0
            && data->envp[j][ft_strlen(var)] == '=')
        {
            free(data->envp[j]);
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
    int i;

    i = 1;
    if (!command->full_cmd[1])
        return;
    while (command->full_cmd[i])
    {
        remove_env_var(data, command->full_cmd[i]);
        i++;
    }
}


