/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:12:21 by rsham             #+#    #+#             */
/*   Updated: 2025/04/16 17:17:21 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execution_process(t_data *data)
{
	if (piping(data))
	{
		free(data->pipe_fd);
		data->pipe_fd = NULL;
		return (1);
	}
	if (setup_children(data))
	{
		clean_pids_pipes(data);
		return (1);
	}
	close_pipes(data, data->cmd_count);
	return (0);
}

int	not_pipeline(t_data *data)
{
	data->cmd_count = count_commands(*data->commands);
	if (data->cmd_count == 0)
	{
		free_list_exec(data->commands);
		return (data->last_exit_status);
	}
	if (data->cmd_count == 1 && built_ins(*data->commands, data))
		return (data->last_exit_status);
	return (-1);
}

int	execute_pipeline(t_data *data)
{
	data->pids = malloc(sizeof(pid_t) * data->cmd_count);
	if (!data->pids)
	{
		free_list_exec(data->commands);
		return (1);
	}
	if (execution_process(data))
	{
		clean_pids_pipes(data);
		return (data->last_exit_status);
	}
	wait_for_children(data, data->cmd_count, &(data->last_exit_status));
	clean_pids_pipes(data);
	free_list_exec(data->commands);
	free(data->commands);
	data->commands = NULL;
	return (data->last_exit_status);
}

void	clean_exe_list(t_data *data)
{
	free_list_exec(data->commands);
	free(data->commands);
	data->commands = NULL;
}

int	executor(t_data *data)
{
	int	exit_status;
	int	cmd_num;

	if (data->stop == 1)
	{
		cleanup_redirections(*data->commands);
		clean_exe_list(data);
		return (1);
	}
	cmd_num = count_commands(*(data)->commands);
	if (cmd_num < 1 || data->error == 1)
		return (1);
	exit_status = not_pipeline(data);
	if (exit_status != -1)
	{
		clean_exe_list(data);
		return (exit_status);
	}
	execute_pipeline(data);
	return (data->last_exit_status);
}
