/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:16:04 by laburomm          #+#    #+#             */
/*   Updated: 2025/04/15 18:45:07 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_atoi_exit(const char *str, char **endptr)
{
    int result;
    int sign;

    result = 0;
    sign = 1;
    while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
        str++;
    if (*str == '+' || *str == '-')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    if (endptr)
        *endptr = (char *)str;
    return result * sign;
}

void ft_exit(t_command *command, t_data *data)
{
    int     status;
    char    *endptr;

    if (data->cmd_count == 1)
        ft_putstr_fd("exit\n", 1);
    if (!command->exe_cmd[1])
    {
        g_exit_status = 0;
        cleanup_shell(data);
        exit(0);
    }
    if (command->exe_cmd[2])
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        g_exit_status = 1;
        return; // Don't exit, just return to shell
    }
    status = ft_atoi_exit(command->exe_cmd[1], &endptr);
    if (*endptr != '\0')
    {
        ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
        g_exit_status = 2;
        cleanup_shell(data);
        exit(2);
    }
    g_exit_status = status;
    cleanup_shell(data);
    exit(status);
}


