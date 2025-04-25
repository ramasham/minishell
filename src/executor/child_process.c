/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:23:23 by rsham             #+#    #+#             */
/*   Updated: 2025/04/23 19:10:22 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_child_failure(t_command *cmd, t_data *data, int exit_code)
{
	cleanup_redirections(cmd);
	cleanup_exe(data);
	exit(exit_code);
}

void	child_process(t_data *data, t_command *cmd)
{
	if (ft_strcmp(cmd->exe_cmd[0], "exit") == 0)
		ft_exit(cmd, data);
	if (!built_ins_pipline(cmd, data))
	{
		if (get_cmd_path(cmd, data) == 2)
			exit(127);
		if (!cmd->full_path)
		{
			ft_error(cmd->exe_cmd[0], "command not found");
			handle_child_failure(cmd, data, 127);
		}
	}
	if (setup_fds(cmd) != 0)
		handle_child_failure(cmd, data, 1);
	pre_exec_checks(cmd, data);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(cmd->full_path, cmd->exe_cmd, data->envp);
	handle_execve_error(cmd, data);
}

static void	close_unused_fds(t_data *data, t_command *current)
{
	t_command	*tmp;

	tmp = *data->commands;
	while (tmp)
	{
		if (tmp != current)
		{
			if (tmp->outfile_fd != -1)
			{
				close(tmp->outfile_fd);
				tmp->outfile_fd = -1;
			}
			if (tmp->infile_fd != -1)
			{
				close(tmp->infile_fd);
				tmp->infile_fd = -1;
			}
			if (tmp->heredoc_fd != -1 && tmp != current)
			{
				close(tmp->heredoc_fd);
				tmp->heredoc_fd = -1;
			}
		}
		tmp = tmp->next;
	}
}

int	forking(t_data *data, t_command *cmd, int i)
{
	data->pids[i] = fork();
	if (data->pids[i] == -1)
	{
		cleanup_exe(data);
		return (1);
	}
	if (data->pids[i] == 0)
	{
		setup_pipes(data, i);
		close_pipes(data, data->cmd_count);
		close_unused_fds(data, cmd);
		child_process(data, cmd);
	}
	else
		cleanup_redirections(cmd);
	return (0);
}

int	setup_children(t_data *data)
{
	int			i;
	t_command	*cmd;

	i = 0;
	cmd = (*data->commands);
	while (cmd)
	{
		if (forking(data, cmd, i))
			return (1);
		cmd = cmd->next;
		i++;
	}
	return (0);
}
