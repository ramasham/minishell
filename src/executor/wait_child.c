/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:02:03 by rsham             #+#    #+#             */
/*   Updated: 2025/04/23 14:23:36 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_wait_status(int status, int *exit_status, t_data *data)
{
	if (WIFEXITED(status))
	{
		*exit_status = WEXITSTATUS(status);
		if (*exit_status == 0)
			data->last_exit_status = 0;
	}
	else if (WIFSIGNALED(status))
	{
		*exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr_fd("Quit (core dumped)\n", 2);
			data->last_exit_status = 131;
		}
	}
	else
		*exit_status = 1;
}

void	wait_for_children(t_data *data, int cmd_count, int *exit_status)
{
	int			i;
	int			status;
	t_command	*cmd;

	i = 0;
	while (i < cmd_count)
	{
		cleanup_redirections((*data->commands));
		signal(SIGINT, SIG_IGN);
		waitpid(data->pids[i], &status, 0);
		handle_wait_status(status, exit_status, data);
		i++;
	}
	cmd = *data->commands;
	while (cmd)
	{
		cleanup_redirections(cmd);
		cmd = cmd->next;
	}
}
