/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:23:23 by rsham             #+#    #+#             */
/*   Updated: 2025/04/16 19:37:43 by rsham            ###   ########.fr       */
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
	get_cmd_path(cmd, data);
	if (!cmd->full_path)
	{
		ft_error(cmd->exe_cmd[0], "command not found");
		handle_child_failure(cmd, data, 127);
	}
	if (setup_fds(cmd) != 0)
		handle_child_failure(cmd, data, 1);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	pre_exec_checks(cmd, data);
	execve(cmd->full_path, cmd->exe_cmd, data->envp);
	handle_execve_error(cmd, data);
}

void	setup_pipes(t_data *data, int i)
{
	if (i > 0)
	{
		if (dup2(data->pipe_fd[(i - 1) * 2], STDIN_FILENO) == -1)
		{
			perror("dup2 failed for input pipe");
			return ;
		}
	}
	if (i < data->cmd_count - 1)
	{
		if (dup2(data->pipe_fd[i * 2 + 1], STDOUT_FILENO) == -1)
		{
			perror("dup2 failed for output pipe");
			return ;
		}
	}
}

int	forking(t_data *data, t_command *cmd, int i)
{
	t_command *tmp;

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
		tmp = *data->commands;
		while (tmp)
		{
			if (tmp != cmd)
			{
				if (tmp->outfile_fd != -1)
					close(tmp->outfile_fd);
				if (tmp->infile_fd != -1)
					close(tmp->infile_fd);
			}
			tmp = tmp->next;
		}
		child_process(data, cmd);
	}
	else
	{
		if (cmd->outfile_fd != -1)
		{
			close(cmd->outfile_fd);
			cmd->outfile_fd = -1;
		}
		if (cmd->infile_fd != -1)
		{
			close(cmd->infile_fd);
			cmd->infile_fd = -1;
		}
	}
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
