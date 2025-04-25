/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:05:37 by rsham             #+#    #+#             */
/*   Updated: 2025/04/23 19:47:27 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_cmd_fields(t_command *cmd)
{
	cmd->append = 0;
	cmd->heredoc_fd = -1;
	cmd->infile_fd = -1;
	cmd->outfile_fd = -1;
	cmd->output_file = NULL;
	cmd->input_file = NULL;
	cmd->heredoc_delim = NULL;
	cmd->heredoc_input = NULL;
	cmd->quoted = 0;
	cmd->skip = 0;
}

static int	handle_redirection_error(t_data *data)
{
	free_list_cmd(data->commands);
	free(data->commands);
	data->commands = NULL;
	return (1);
}

static int	handle_cleanup_and_exit(t_data *data)
{
	free_list_exec(data->commands);
	free(data->commands);
	data->commands = NULL;
	return (1);
}

int	set_commands(t_data *data)
{
	int			empty_found;
	t_command	*cmd;

	empty_found = 1;
	get_command(data, *(data->node));
	cmd = *(data->commands);
	while (cmd)
	{
		init_cmd_fields(cmd);
		if (parse_redirection(cmd, data))
			return (handle_redirection_error(data));
		if (create_exec_cmd(data, cmd))
			return (1);
		remove_quotes_from_command(cmd);
		trim_cmd_quotes(cmd);
		if (cmd->exe_cmd && cmd->exe_cmd[0])
			empty_found = 0;
		cmd = cmd->next;
	}
	if (empty_found)
	{
		// return (1);
		return (handle_cleanup_and_exit(data));
	}
	return (0);
}
