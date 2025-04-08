/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:05:37 by rsham             #+#    #+#             */
/*   Updated: 2025/04/08 18:38:37 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_commands(t_data *data)
{   
    get_command(data, *(data->node));
    get_cmd_path(*(data->commands), data);
    printf("cmd list:");
    print_command(data);
    (*data->commands)->append = 0;
    (*data->commands)->heredoc_fd = -1;
    (*data->commands)->infile_fd = STDIN_FILENO;
    (*data->commands)->outfile_fd = STDOUT_FILENO;
    (*data->commands)->output_file = NULL;
    (*data->commands)->input_file = NULL;
}
