/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:12:21 by rsham             #+#    #+#             */
/*   Updated: 2025/04/08 23:33:55 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execution_process(t_data *data)
{
    if (piping(data))
    {
        free(data->pipe_fd);
        data->pipe_fd = NULL;
        return (1);
    }
    if (setup_children(data))
    {
        free(data->pipe_fd);
        free(data->pids);
        data->pipe_fd = NULL;
        data->pids = NULL;
        return (1);
    }
    close_pipes(data, data->cmd_count);
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
    if (data->cmd_count == 1 && built_ins(*data->commands, data))
    {
        return (data->last_exit_status);
    }
    return (-1);
}

int execute_pipeline(t_data *data)
{

    data->pids = malloc(sizeof(pid_t) * data->cmd_count);
    if (!data->pids)
    {
        free_list_cmd(data->commands);
        return(1);
    }
    if (execution_process(data))
    {
        free(data->pids);
        data->pids = NULL;
        free(data->pipe_fd);
        data->pipe_fd = NULL;
        return (data->last_exit_status);
    }
    wait_for_children(data, data->cmd_count, &(data->last_exit_status));
    free(data->pids);
    free(data->pipe_fd);
    free_list_cmd(data->commands);
    free(data->commands);
    data->pids = NULL;
    data->pipe_fd = NULL;
    data->commands = NULL;
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
        free(data->commands);
        data->commands = NULL;
        return (exit_status);
    }
    execute_pipeline(data);
    return (data->last_exit_status);
}
