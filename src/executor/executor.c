/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:12:21 by rsham             #+#    #+#             */
/*   Updated: 2025/03/22 23:41:14 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    execution_process(t_data *data, int **pipe_fd, pid_t *pids)
{
    if (piping(data, pipe_fd))
        return(1);
    if (create_children(data, *pipe_fd, pids))
    {
        free(*pipe_fd);
        free(pids);
        return(1);
    }
    close_pipes(*pipe_fd, data->cmd_count);
    return (0);
}

int not_pipeline(t_data *data)
{
    data->cmd_count = count_commands(*data->commands);
    if (data->cmd_count == 0)
    {
        free_list_cmd(data->commands);
        return (data->last_exit_status);
    }
    // if (data->cmd_count == 1 && built_ins(*data->commands, data))
    // {
    //     data->last_exit_status = 0;
    //     free_list_cmd(data->commands);
    //     return;
    // }
    if (data->cmd_count == 1 && built_ins(*data->commands, data))
    {
        return (data->last_exit_status);
    }
    return (-1);
}

int execute_pipeline(t_data *data)
{
    int   *pipe_fd;
    pid_t *pids;

    pipe_fd = NULL;
    pids = malloc(sizeof(pid_t) * data->cmd_count);
    if (!pids)
    {
        free_list_cmd(data->commands);
        return(1);
    }
    if (execution_process(data, &pipe_fd, pids))
    {
        free(pids);
        return (data->last_exit_status);
    }
    wait_for_children(data, pids, data->cmd_count, &(data->last_exit_status));
    if (pipe_fd)
        free(pipe_fd);
    free(pids);
    free_list_cmd(data->commands);
    return (data->last_exit_status);
}


int executor(t_data *data)
{
    int exit_status;
    int dot_slash_status;

    dot_slash_status = handle_dot_slash_exec(data);
    if (dot_slash_status != 0)
    {
        return (dot_slash_status);
    }
    exit_status = not_pipeline(data);
    if (exit_status != -1)
    {
        free_list_cmd(data->commands);
        return (exit_status);
    }
    else
    {
        execute_pipeline(data);
        // free_list_cmd(data->commands);
        // free(data->commands);
        // data->commands = NULL;
    }
    return (data->last_exit_status);
}
