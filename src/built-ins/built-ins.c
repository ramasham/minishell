/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:27:57 by laburomm          #+#    #+#             */
/*   Updated: 2025/04/23 14:20:35 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_ins(t_command *command, t_data *data)
{
	int	stdin_backup;
	int	stdout_backup;

	if (!command || !command->exe_cmd || !command->exe_cmd[0]
		|| !is_built_in(command->exe_cmd[0]))
		return (0);
	if (save_fds(&stdin_backup, &stdout_backup))
		return (0);
	if (setup_fds(command) != 0)
	{
		restore_fds(stdin_backup, stdout_backup);
		return (0);
	}
	execute_builtins(command, data);
	restore_fds(stdin_backup, stdout_backup);
	cleanup_redirections(command);
	return (1);
}

int	built_ins_pipline(t_command *command, t_data *data)
{
	int	stdin_backup;
	int	stdout_backup;

	if (!command || !command->exe_cmd || !command->exe_cmd[0]
		|| !is_built_in(command->exe_cmd[0]))
		return (0);
	if (save_fds(&stdin_backup, &stdout_backup))
		return (0);
	if (setup_fds(command) != 0)
	{
		restore_fds(stdin_backup, stdout_backup);
		return (0);
	}
	execute_builtins(command, data);
	restore_fds(stdin_backup, stdout_backup);
	clean_pids_pipes(data);
	cleanup_redirections(command);
	free_env(data->envp);
	clean_exe_list(data);
	exit(1);
}
