/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:36:05 by rsham             #+#    #+#             */
/*   Updated: 2025/04/15 18:09:44 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     count_commands(t_command *cmds)
{
    int i;

    i = 0;
    if (!cmds)
        return (0);
    while (cmds)
    {
        i++;
        cmds = cmds->next;
    }
    return (i);
}
