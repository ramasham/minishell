/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:12:21 by rsham             #+#    #+#             */
/*   Updated: 2025/03/08 01:38:05 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    execution_process(t_data *data, int **pipe_fd, pid_t *pids)
{
    piping(data, pipe_fd);
    create_children(data, *pipe_fd, pids);
    close_pipes(*pipe_fd, data->cmd_count);
}

void executor(t_data *data)
{
    int   *pipe_fd;
    pid_t *pids;

    pipe_fd = NULL;
    data->cmd_count = count_commands(*data->commands);
    if (data->cmd_count == 0)
        return;
    if (data->cmd_count == 1 && built_ins(*data->commands, data))
    {
        data->last_exit_status = 0;
        free_list_cmd(data->commands);
        return;
    }
    pids = malloc(sizeof(pid_t) * data->cmd_count);
    if (!pids)
        exit(1);
    execution_process(data, &pipe_fd, pids);
    wait_for_children(data, pids, data->cmd_count, &(data->last_exit_status));
    free(pipe_fd);
    free(pids);
    free_list_cmd(data->commands);
}
