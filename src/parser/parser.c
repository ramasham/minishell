/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:05:37 by rsham             #+#    #+#             */
/*   Updated: 2025/04/09 16:57:58 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_commands(t_data *data)
{   
    t_command *cmd;

    get_command(data, *(data->node));
    get_cmd_path(*(data->commands), data);    
    cmd = *(data->commands);
    while (cmd)
    {
        cmd->append = 0;
        cmd->heredoc_fd = -1;
        cmd->infile_fd = STDIN_FILENO;
        cmd->outfile_fd = STDOUT_FILENO;
        cmd->output_file = NULL;
        cmd->input_file = NULL;
        cmd->heredoc_delim = NULL;
        cmd->heredoc_input = NULL;
        cmd->quoted = 0;
        parse_redirection(cmd, data);
        cmd = cmd->next;
    }
}
