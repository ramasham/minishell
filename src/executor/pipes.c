/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:37:59 by rsham             #+#    #+#             */
/*   Updated: 2025/03/05 21:41:53 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void piping(t_data *data, int **pipe_fd)
{
    int i;

    *pipe_fd = malloc(sizeof(int) * 2 * (data->cmd_count - 1));
    if (!*pipe_fd)
    {
        perror("malloc fot pipe failed");
        exit(1);
    }
    i = 0;
    while (i < data->cmd_count - 1)
    {
        if (pipe(*pipe_fd + (i * 2)) == -1)
        {
            perror("pipe failed");
            free(*pipe_fd);
            exit(1);
        }
        i++;
    }
}

void close_pipes(int *pipe_fd, int cmd_count)
{
    int i;
    
    i = 0;
    while (i < 2 * (cmd_count - 1))
    {
        if (close(pipe_fd[i]) == -1)
            perror("closed failed");
        i++;
    }
}
