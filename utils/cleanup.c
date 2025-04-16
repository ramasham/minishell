/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:30:54 by rsham             #+#    #+#             */
/*   Updated: 2025/04/16 19:26:46 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds_and_cleanup(t_command *cmd)
{
	if (cmd->outfile_fd != -1)
	{
		fprintf (stderr, " close in child %d\n", cmd->outfile_fd);
		close(cmd->outfile_fd);
	}
	if (cmd->infile_fd != -1)
	{
		fprintf (stderr, "close in child %d\n", cmd->infile_fd);
		close(cmd->infile_fd);
	}
	cleanup_heredoc(cmd);
}

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
		close(cmd->heredoc_fd);
	if (cmd->heredoc_delim)
		free(cmd->heredoc_delim);
	cmd->heredoc_fd = -1;
	cmd->heredoc_delim = NULL;
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
		fprintf(stderr, "%d\n", cmd->infile_fd);
		close(cmd->infile_fd);
	}
	fprintf(stderr, "THE FIRST: %d\n", cmd->outfile_fd);
	if (cmd->outfile_fd != -1)
	{
		close(cmd->outfile_fd);
		fprintf(stderr, "THE SECOND: %d\n", cmd->outfile_fd);
	}
	cleanup_heredoc(cmd);
	// cmd->infile_fd = -1;
	// cmd->outfile_fd = -1;
	cmd->heredoc_fd = -1;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->heredoc_delim = NULL;
}
