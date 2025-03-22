/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_abs_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:59:18 by rsham             #+#    #+#             */
/*   Updated: 2025/03/11 22:02:49 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_abs_path(char *cmd)
{
    if (!cmd)
        return (0);
    if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
        return (1);
    return (0);
}

int handle_abs_path(t_command *cmd)
{
    if (!cmd || !cmd->full_cmd[0])
        return (1);
    if (access(cmd->full_cmd[0], X_OK) == 0)
    {
        cmd->full_path = ft_strdup(cmd->full_cmd[0]);
        if(!cmd->full_path)
            return (1);
        return (0);
    }
    return (1);
}
