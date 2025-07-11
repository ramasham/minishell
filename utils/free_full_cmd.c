/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_full_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:59:53 by rsham             #+#    #+#             */
/*   Updated: 2025/04/22 17:21:20 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_full_cmd(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->full_cmd)
	{
		i = 0;
		while (cmd->full_cmd[i])
			free(cmd->full_cmd[i++]);
		free(cmd->full_cmd);
		cmd->full_cmd = NULL;
	}
	if (cmd->full_path)
	{
		free(cmd->full_path);
		cmd->full_path = NULL;
	}
	free(cmd);
}

void	free_list_cmd(t_command **cmds)
{
	t_command	*tmp;

	if (!cmds || !*cmds)
		return ;
	while (*cmds)
	{
		tmp = *cmds;
		*cmds = (*cmds)->next;
		free_full_cmd(tmp);
	}
	*cmds = NULL;
}

void	cleanup_cmd(t_data *data)
{
	if (data->pipe_fd)
		free(data->pipe_fd);
	if (data->pids)
		free(data->pids);
	free_list_cmd(data->commands);
	free(data->commands);
	free_env(data->envp);
}
