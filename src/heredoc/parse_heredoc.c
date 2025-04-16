/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:36:34 by rsham             #+#    #+#             */
/*   Updated: 2025/04/16 14:19:21 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	stop(t_command *cmd, char *line)
{
	int	line_len;
	int	delim_len;

	if (!line || !cmd->heredoc_delim)
		return (1);
	line_len = ft_strlen(line);
	delim_len = ft_strlen(cmd->heredoc_delim);
	if (ft_strcmp(line, cmd->heredoc_delim) == 0 && (line_len == delim_len))
		return (1);
	return (0);
}

static void	update_heredoc_delim(t_command *cmd, char *tmp)
{
	if (tmp)
	{
		free(cmd->heredoc_delim);
		cmd->heredoc_delim = tmp;
	}
	else
	{
		free(cmd->heredoc_delim);
		cmd->heredoc_delim = NULL;
	}
}

void	heredoc_delim(t_command *cmd, int *i)
{
	char	*tmp;

	cmd->heredoc_delim = ft_strdup(cmd->full_cmd[*i + 1]);
	if (!cmd->heredoc_delim)
		return ;
	if (cmd->heredoc_delim[0] == '"')
	{
		cmd->quoted = 1;
		tmp = ft_strremove(cmd->heredoc_delim, "\"");
		update_heredoc_delim(cmd, tmp);
	}
	else if (cmd->heredoc_delim[0] == '\'')
	{
		tmp = ft_strremove(cmd->heredoc_delim, "'");
		update_heredoc_delim(cmd, tmp);
	}
}

int	parse_heredoc(t_command *cmd, int *i, t_data *data)
{
	if (!cmd->full_cmd[*i + 1])
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (1);
	}
	heredoc_delim(cmd, i);
	cmd->heredoc_fd = handle_heredoc(cmd, data);
	data->last_exit_status = g_exit_status;
	if (data->last_exit_status == 130)
		data->stop = 1;
	if (cmd->heredoc_fd == -1)
	{
		free(cmd->heredoc_delim);
		cmd->heredoc_delim = NULL;
		return (1);
	}
	if (cmd->infile_fd != -1)
		close(cmd->infile_fd);
	cmd->infile_fd = cmd->heredoc_fd;
	free(cmd->heredoc_delim);
	cmd->heredoc_delim = NULL;
	*i += 2;
	return (0);
}
