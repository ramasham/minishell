/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:49:36 by rsham             #+#    #+#             */
/*   Updated: 2025/03/08 01:49:57 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(t_command *command)
{
    int i;
    int newline;
    int fd;

    i = 1;
    newline = 1;
    fd = command->outfile;
    if (command->full_cmd[1] && ft_strcmp(command->full_cmd[1], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    while (command->full_cmd[i])
    {
        write(fd, command->full_cmd[i], ft_strlen(command->full_cmd[i]));
        if (command->full_cmd[i + 1])
            write(fd, " ", 1);
        i++;
    }
    if (newline)
        write(fd, "\n", 1);
}
