/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:30:54 by rsham             #+#    #+#             */
/*   Updated: 2025/04/23 14:15:49 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_pids_pipes(t_data *data)
{
	free(data->pids);
	data->pids = NULL;
	free(data->pipe_fd);
	data->pipe_fd = NULL;
}

void	cleanup_heredoc(t_command *cmd)
{
	if (cmd->heredoc_fd != -1)
	{
		close(cmd->heredoc_fd);
		cmd->heredoc_fd = -1;
	}
	if (cmd->heredoc_delim)
	{
		free(cmd->heredoc_delim);
		cmd->heredoc_delim = NULL;
	}
}

void	cleanup_shell(t_data *data)
{
	if (!data)
		return ;
	if (data->input)
		free(data->input);
	if (data->node && *data->node)
	{
		free_list(data->node);
		free(data->node);
	}
	if (data->commands)
	{
		free_list_exec(data->commands);
		free(data->commands);
	}
	if (data->envp)
		free_env(data->envp);
	if (data->pids)
		free(data->pids);
	if (data->pipe_fd)
		free(data->pipe_fd);
}

void	cleanup_redirections(t_command *cmd)
{
	if (cmd->infile_fd != -1)
	{
		close(cmd->infile_fd);
		cmd->infile_fd = -1;
	}
	if (cmd->outfile_fd != -1)
	{
		close(cmd->outfile_fd);
		cmd->outfile_fd = -1;
	}
	cleanup_heredoc(cmd);
	cmd->input_file = NULL;
	cmd->output_file = NULL;
}
