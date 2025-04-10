/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:05:37 by rsham             #+#    #+#             */
/*   Updated: 2025/04/10 20:01:58 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int set_commands(t_data *data)
{   
    t_command *cmd;
    int cmd_num;

    cmd_num = 0;
    get_command(data, *(data->node));
    get_cmd_path(*(data->commands), data);
    cmd = *(data->commands);
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
        parse_redirection(cmd, data);
        cmd = cmd->next;
    }
    remove_empty_commands(data->commands);
    cmd_num = count_commands(*data->commands);
    if (cmd_num <= 0)
    {
        return (1);
    }
    return (0);
}
