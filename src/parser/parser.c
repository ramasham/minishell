/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:05:37 by rsham             #+#    #+#             */
/*   Updated: 2025/02/25 19:38:17 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int     set_pipes(t_command *cmd)
// {
    
// }
void    set_commands(t_data *data, char **envp)
{
    get_command(data, *(data->node));
    get_cmd_path(*(data->commands), envp);
    print_command_info(*(data->commands));
}