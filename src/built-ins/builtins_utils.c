/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:13:56 by rsham             #+#    #+#             */
/*   Updated: 2025/04/21 18:14:16 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_in(char *cmd)
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