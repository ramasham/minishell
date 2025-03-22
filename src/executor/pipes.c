/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:37:59 by rsham             #+#    #+#             */
/*   Updated: 2025/03/22 21:04:14 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int piping(t_data *data)
{
    int i;

    data->pipe_fd = malloc(sizeof(int) * 2 * (data->cmd_count - 1));
    if (!data->pipe_fd)
    {
        perror("malloc fot pipe failed");
        return(1);
    }
    i = 0;
    while (i < data->cmd_count - 1)
    {
        if (pipe(data->pipe_fd + (i * 2)) == -1)
        {
            perror("pipe failed");
            free(data->pipe_fd);
            data->pipe_fd = NULL;
            return(1);
        }
        i++;
    }
    return (0);
}

void close_pipes(t_data *data, int cmd_count)
{
    int i;
    
    i = 0;
    while (i < 2 * (cmd_count - 1))
    {
        if (close(data->pipe_fd[i]) == -1)
            perror("closed failed");
        i++;
    }
}

// void cleanup_pipes(t_data *data)
// {
//     if (data->pipe_fd)
//     {
//         free(data->pipe_fd);
//         data->pipe_fd = NULL;
//     }
// }
