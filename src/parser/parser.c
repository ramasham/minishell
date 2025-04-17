/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:05:37 by rsham             #+#    #+#             */
/*   Updated: 2025/04/17 20:50:37 by rsham            ###   ########.fr       */
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

void	trim_cmd_quotes(t_command *cmd)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (cmd->exe_cmd && cmd->exe_cmd[i])
	{
		char *arg = cmd->exe_cmd[i];
		int len = ft_strlen(arg);

		if ((arg[0] == '\'' && arg[len - 1] == '\'')
			|| (arg[0] == '"' && arg[len - 1] == '"'))
		{
			trimmed = ft_strtrim(arg, (arg[0] == '\'') ? "'" : "\"");
			if (trimmed)
			{
				free(cmd->exe_cmd[i]);
				cmd->exe_cmd[i] = trimmed;
			}
		}
		i++;
	}
}


int	set_commands(t_data *data)
{
	t_command	*cmd;

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
		cmd = cmd->next;
	}
	if (data->empty)
		return (handle_cleanup_and_exit(data));
	get_cmd_path(*(data->commands), data);
	return (0);
}
