/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:49:36 by rsham             #+#    #+#             */
/*   Updated: 2025/04/09 16:12:30 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(t_data *data, t_command *cmd)
{
    int i;
    int newline;
    
    i = 1;
    newline = 1;
    if (cmd->full_cmd[1] && ft_strcmp(cmd->full_cmd[1], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    while (cmd->full_cmd[i])
    {
        write(STDOUT_FILENO, cmd->full_cmd[i], ft_strlen(cmd->full_cmd[i]));
        if (cmd->full_cmd[i + 1])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (newline)
        write(STDOUT_FILENO, "\n", 1);
    data->last_exit_status = 0;
}

