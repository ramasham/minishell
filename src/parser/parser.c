/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:05:37 by rsham             #+#    #+#             */
/*   Updated: 2025/04/08 23:01:08 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_commands(t_data *data)
{   
    get_command(data, *(data->node));
    get_cmd_path(*(data->commands), data);
    
    // Initialize command structure
    t_command *cmd = *(data->commands);
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
        
        // Parse redirections for this command
        parse_redirection(cmd);
        
        cmd = cmd->next;
    }
}
