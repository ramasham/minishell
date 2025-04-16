/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:22:07 by rsham             #+#    #+#             */
/*   Updated: 2025/04/16 12:53:07 by rsham            ###   ########.fr       */
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
		cleanup_redirections(cmd);
		cleanup_exe(data);
		exit(126);
	}
}
