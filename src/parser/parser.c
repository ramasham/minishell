/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:05:37 by rsham             #+#    #+#             */
/*   Updated: 2025/04/12 19:33:02 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_empty_commands(t_command **cmd_list)
{
	t_command *prev;
	t_command *curr;
	t_command *next;
    
    prev = NULL;
    curr = *cmd_list;
	while (curr)
	{
		next = curr->next;
		if (!curr->full_cmd || !curr->full_cmd[0])
		{
			if (prev)
				prev->next = next;
			else
				*cmd_list = next;
            if (curr->skip == 1)
                cleanup_redirections(curr);
			free(curr->full_cmd);
			free(curr);
		}
		else
			prev = curr;
		curr = next;
	}
}

int set_commands(t_data *data)
{   
    t_command *cmd;
    int cmd_num;
    int redirection_error;

    get_command(data, *(data->node));
    get_cmd_path(*(data->commands), data);
    cmd_num = 0;
    cmd = *(data->commands);
    redirection_error = 0;
    while (cmd)
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
        if (parse_redirection(cmd, data))
        {
            redirection_error = 1;
            break;
        }
        cmd = cmd->next;
    }
    if (redirection_error)
    {
        free_list_cmd((data->commands));
        free(data->commands);
        data->commands = NULL;
        return (1);
    }
    remove_empty_commands(data->commands);
    cmd_num = count_commands(*data->commands);
    if (cmd_num <= 0)
        return (1);
    return (0);
}
