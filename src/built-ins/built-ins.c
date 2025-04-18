/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:27:57 by laburomm          #+#    #+#             */
/*   Updated: 2025/04/16 18:47:41 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtinn(char *cmd)
{
	return (cmd && (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
			|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
			|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
			|| !ft_strcmp(cmd, "exit")));
}

void	execute_builtins(t_command *command, t_data *data)
{
	if (!command || !command->exe_cmd || !command->exe_cmd[0])
		return ;
	if (!ft_strcmp(command->exe_cmd[0], "echo"))
		ft_echo(data, command);
	else if (!ft_strcmp(command->exe_cmd[0], "cd"))
		ft_cd(data, command->exe_cmd[1]);
	else if (!ft_strcmp(command->exe_cmd[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(command->exe_cmd[0], "export"))
		ft_export(data, command);
	else if (!ft_strcmp(command->exe_cmd[0], "unset"))
		ft_unset(data, command);
	else if (!ft_strcmp(command->exe_cmd[0], "env"))
		ft_env(data->envp);
}

int	save_fds(int *stdin_backup, int *stdout_backup)
{
	*stdin_backup = dup(STDIN_FILENO);
	*stdout_backup = dup(STDOUT_FILENO);
	return (*stdin_backup == -1 || *stdout_backup == -1);
}

void	restore_fds(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}

int	built_ins(t_command *command, t_data *data)
{
	int	stdin_backup;
	int	stdout_backup;

	if (!command || !command->exe_cmd || !command->exe_cmd[0]
		|| !is_builtinn(command->exe_cmd[0]))
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
