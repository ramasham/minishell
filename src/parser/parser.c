/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:05:37 by rsham             #+#    #+#             */
/*   Updated: 2025/04/10 14:49:09 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int is_valid_assignment(char *str)
{
    int i = 0;

    if (!str || (!ft_isalpha(str[i]) && str[i] != '_'))
        return (0);
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (str[i] == '=');
}


static void handle_assignment(char *assignment, t_data *data)
{
    char    *name;
    char    *value;
    int     i;
    if (!assignment || !data)
        return ;
    i = 0;
    while (assignment[i] && assignment[i] != '=')
        i++;
    if (!assignment[i]) // no '=' found
        return ;
    name = ft_substr(assignment, 0, i);
    value = ft_strdup(assignment + i + 1);
    if (!name || !value)
    {
        free(name);
        free(value);
        return ;
    }
    if (is_in_export_only(data->export_only, name))
        remove_from_export_only(data, name, ft_strlen(name));

    my_setenv(data, name, value, 1); // overwrite if exists
    free(name);
    free(value);
}


void set_commands(t_data *data)
{   
    t_command *cmd;

    get_command(data, *(data->node));
    get_cmd_path(*(data->commands), data);    
    cmd = *(data->commands);
    if (is_valid_assignment(cmd->full_cmd[0]))
    {
        handle_assignment(cmd->full_cmd[0], data);
        return ; // skip execution
    }
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
