/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:37:59 by rsham             #+#    #+#             */
/*   Updated: 2025/04/23 18:52:13 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	piping(t_data *data)
{
	int	i;

	data->pipe_fd = malloc(sizeof(int) * 2 * (data->cmd_count - 1));
	if (!data->pipe_fd)
	{
		perror("pipe allocation failed");
		return (1);
	}
	i = 0;
	while (i < data->cmd_count - 1)
	{
		if (pipe(data->pipe_fd + (i * 2)) == -1)
		{
			perror("pipe");
			free(data->pipe_fd);
			data->pipe_fd = NULL;
			return (1);
		}
		i++;
	}
	return (0);
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

void	close_pipes(t_data *data, int cmd_count)
{
	int	i;

	if (!data->pipe_fd)
		return ;
	i = 0;
	while (i < 2 * (cmd_count - 1))
	{
		if (close(data->pipe_fd[i]) == -1)
		{
			perror("Failed to close pipe file descriptor");
			return ;
		}
		if (close(data->pipe_fd[i + 1]) == -1)
		{
			perror("Failed to close pipe file descriptor");
			return ;
		}
		i += 2;
	}
}
