/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exe_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:43:38 by rsham             #+#    #+#             */
/*   Updated: 2025/04/16 14:04:06 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exec_cmd(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->exe_cmd)
	{
		i = 0;
		while (cmd->exe_cmd[i])
			free(cmd->exe_cmd[i++]);
		free(cmd->exe_cmd);
		cmd->exe_cmd = NULL;
	}
	if (cmd->full_path)
	{
		free(cmd->full_path);
		cmd->full_path = NULL;
	}
	free(cmd);
}

// free a list of commands
void	free_list_exec(t_command **cmds)
{
	t_command	*tmp;

	if (!cmds || !*cmds)
		return ;
	while (*cmds)
	{
		tmp = *cmds;
		*cmds = (*cmds)->next;
		free_exec_cmd(tmp);
	}
	*cmds = NULL;
}

void	cleanup_exe(t_data *data)
{
	if (data->pipe_fd)
		free(data->pipe_fd);
	if (data->pids)
		free(data->pids);
	free_exec_cmd(*data->commands);
	free(data->commands);
	free_env(data->envp);
}
