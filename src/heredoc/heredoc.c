/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:48:26 by laburomm          #+#    #+#             */
/*   Updated: 2025/04/23 19:25:40 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipe_and_fork(int pipe_fd[2], pid_t *pid)
{
	if (pipe(pipe_fd) == -1)
		return (-1);
	*pid = fork();
	if (*pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	return (0);
}

void	write_to_pipe(t_command *cmd, int *pipe_fd, char *expanded,
		t_data *data)
{
	if (cmd->quoted)
	{
		expanded = expand_heredoc_content(cmd->heredoc_input, data);
		if (expanded)
		{
			write(pipe_fd[1], expanded, ft_strlen(expanded));
			write(pipe_fd[1], "\n", 1);
			free(expanded);
		}
	}
	else
	{
		write(pipe_fd[1], cmd->heredoc_input, ft_strlen(cmd->heredoc_input));
		write(pipe_fd[1], "\n", 1);
	}
}

int	handle_heredoc_input(t_command *cmd, int pipe_fd[2], char *expanded,
		t_data *data)
{
	while (1)
	{
		if (g_signo == SIGINT)
		{
			cleanup_redirections(cmd);
			exit(128 + SIGINT);
		}
		cmd->heredoc_input = readline("> ");
		if (!cmd->heredoc_input)
			return (1);
		if (stop(cmd, cmd->heredoc_input))
		{
			free(cmd->heredoc_input);
			cmd->heredoc_input = NULL;
			cleanup_redirections(cmd);
			return (1);
		}
		write_to_pipe(cmd, pipe_fd, expanded, data);
		free(cmd->heredoc_input);
		cmd->heredoc_input = NULL;
	}
	return (0);
}

int	handle_parent_process(int pipe_fd[2], t_data *data, int *status)
{
	signal(SIGINT, SIG_IGN);
	wait(status);
	signal(SIGINT, SIG_DFL);
	close(pipe_fd[1]);
	if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGINT)
	{
		data->last_exit_status = 130;
		data->stop = 1;
		return (-1);
	}

	if (WIFEXITED(*status))
	{
		data->last_exit_status = WEXITSTATUS(*status);
		if (data->last_exit_status == 130)
			data->stop = 1;
		return (pipe_fd[0]);
	}
	return (-1);
}

int	handle_heredoc(t_command *cmd, t_data *data)
{
	int		pipe_fd[2];
	char	*expanded;
	int		status;
	pid_t	pid;

	expanded = NULL;
	if (create_pipe_and_fork(pipe_fd, &pid) == -1)
		return (-1);
	if (pid == 0)
	{
		setup_heredoc_signals();
		close(pipe_fd[0]);
		if (handle_heredoc_input(cmd, pipe_fd, expanded, data))
		{
			cleanup_redirections(cmd);
			cleanup_cmd(data);
			close(pipe_fd[1]);
			if(g_signo ==  SIGINT)
				exit(128 + SIGINT);
			else
				exit(0);
		}
		close(pipe_fd[1]);
		exit(0);
	}
	else
	{
		return (handle_parent_process(pipe_fd, data, &status));
	}
	return (0);
}
