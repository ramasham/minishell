/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <rsham@student.42amman.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:12:21 by rsham             #+#    #+#             */
/*   Updated: 2025/03/10 22:00:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    execution_process(t_data *data, int **pipe_fd, pid_t *pids)
{
    if (piping(data, pipe_fd))
        return(1);
    if (create_children(data, *pipe_fd, pids))
        return(1);
    close_pipes(*pipe_fd, data->cmd_count);
    return (0);
}

void executor(t_data *data)
{
    int   *pipe_fd;
    pid_t *pids;

    pipe_fd = NULL;
    data->cmd_count = count_commands(*data->commands);
    if (data->cmd_count == 0)
    {
        free_list_cmd(data->commands);
        return;
    }
    if (data->cmd_count == 1 && built_ins(*data->commands, data))
    {
        data->last_exit_status = 0;
        free_list_cmd(data->commands);
        return;
    }
    pids = malloc(sizeof(pid_t) * data->cmd_count);
    if (!pids)
    {
        data->last_exit_status = 1;
        free_list_cmd(data->commands);
        return;
    }
    if (execution_process(data, &pipe_fd, pids))
    {
        free(pids);
        exit(data->last_exit_status);
    }
    wait_for_children(data, pids, data->cmd_count, &(data->last_exit_status));
    if (pipe_fd)
        free(pipe_fd);
    free(pids);
    free_list_cmd(data->commands);
}
