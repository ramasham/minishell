/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:22:07 by rsham             #+#    #+#             */
/*   Updated: 2025/04/23 18:16:56 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_execve_error(t_command *cmd, t_data *data)
{
	int	exit_code;

	if (errno == EACCES)
	{
		ft_putstr_fd(": Permission denied\n", 2);
		exit_code = 126;
	}
	else
	{
		perror(cmd->exe_cmd[0]);
		exit_code = 1;
	}
	cleanup_redirections(cmd);
	cleanup_exe(data);
	exit(exit_code);
}

void	pre_exec_checks(t_command *cmd, t_data *data)
{
	struct stat	path_stat;

	if (stat(cmd->full_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_error(cmd->exe_cmd[0], "Is a directory");
		handle_child_failure(cmd, data, 126);
	}
}

int	check_pre_exec_errors(t_data *data)
{
	if (data->stop == 1)
	{
		cleanup_redirections(*data->commands);
		clean_exe_list(data);
		return (1);
	}
	if (count_commands(*data->commands) < 1 || data->error == 1)
		return (1);
	return (0);
}

int	is_single_exit_cmd(t_data *data)
{
	return (data->commands && data->commands[0]
		&& data->commands[0]->exe_cmd
		&& ft_strcmp(data->commands[0]->exe_cmd[0], "exit") == 0
		&& count_commands(*data->commands) == 1);
}

int	handle_exit_case(t_data *data)
{
	ft_exit(data->commands[0], data);
	clean_exe_list(data);
	return (data->last_exit_status);
}
