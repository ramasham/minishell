/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:05:37 by rsham             #+#    #+#             */
/*   Updated: 2025/04/15 19:12:15 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char *remove_quotes(const char *str, int remove_all)
{
    int i;
    int j;

    i = 0;
    j = 0;
    char *result;
    if (!str)
        return (NULL);
    result = malloc(ft_strlen(str) + 1);
    if (!result)
        return (NULL);
    if (remove_all)
    {
        while (str[i] == '"' || str[i] == '\'') 
            i++;
        while (str[i])
        {
            if (str[i] != '"' && str[i] != '\'')
                result[j++] = str[i];
            i++;
        }
        while (j >= 0 && (result[j - 1] == '"' || result[j - 1] == '\''))
            j--;
    } 
    else
    {
        if (str[i] == '\'' || str[i] == '"')
            i++;
        while (str[i])
            result[j++] = str[i++];
    }
    result[j] = '\0';
    return (result);
}

static void remove_quotes_from_command(t_command *cmd)
{
    int i;
    char *stripped;

    if (!cmd || !cmd->full_cmd)
        return;
    i = 0;
    while (cmd->full_cmd[i]) 
    {
        if (i == 0)
            stripped = remove_quotes(cmd->full_cmd[i], 1);
        else if (cmd->full_cmd[i])
            stripped = ft_strdup(cmd->full_cmd[i]);
        else
            stripped = NULL;
        free(cmd->full_cmd[i]);
        cmd->full_cmd[i] = stripped;
        i++;
    }
}

int is_operator(char *str)
{
    return (ft_strcmp(str, "|") == 0
        || ft_strcmp(str, ">") == 0
        || ft_strcmp(str, ">>") == 0
        || ft_strcmp(str, "<") == 0
        || ft_strcmp(str, "<<") == 0);
}


int create_exec_cmd(t_data *data, t_command *cmd)
{
    int i = 0;
    int j = 0;
    int count = 0;

    (void)data;
    if (!cmd->full_cmd)
        return (1);

    // Count non-operator elements (i.e., actual command arguments)
    while (cmd->full_cmd[i])
    {
        if (is_operator(cmd->full_cmd[i]))
        {
            i++;
            if (cmd->full_cmd[i])
                i++;
        }
        else
        {
            count++;
            i++;
        }
    }

    // If no command arguments found, skip exe_cmd creation
    if (count == 0)
    {
        data->empty = 1;
        // Still need to free full_cmd
        i = 0;
        while (cmd->full_cmd[i])
            free(cmd->full_cmd[i++]);
        free(cmd->full_cmd);
        cmd->full_cmd = NULL;
        // cmd->exe_cmd = NULL;
        cleanup_redirections(cmd);
        return (0);
    }

    // Allocate exe_cmd
    cmd->exe_cmd = malloc((count + 1) * sizeof(char *));
    if (!cmd->exe_cmd)
        return (1);

    // Copy non-operator args to exe_cmd
    i = 0;
    j = 0;
    while (cmd->full_cmd[i])
    {
        if (is_operator(cmd->full_cmd[i]))
        {
            i++;
            if (cmd->full_cmd[i])
                i++;
        }
        else
        {
            cmd->exe_cmd[j++] = ft_strdup(cmd->full_cmd[i]);
            i++;
        }
    }
    cmd->exe_cmd[j] = NULL;
    i = 0;
    while (cmd->full_cmd[i])
        free(cmd->full_cmd[i++]);
    free(cmd->full_cmd);
    cmd->full_cmd = NULL;

    return (0);
}


int set_commands(t_data *data)
{    
    t_command   *cmd;
    int         redirection_error;

    get_command(data, *(data->node));
    remove_quotes_from_command(*data->commands);
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
            free_list_cmd(data->commands);
            free(data->commands);
            data->commands = NULL;
            redirection_error = 1;
            break;
        }
        if (create_exec_cmd(data, cmd))
            return (1);
        cmd = cmd->next;
    }
    if (data->empty)
    {
        free_list_exec(data->commands);
        free(data->commands);
        data->commands = NULL;
        return (1);
    }
    if (redirection_error)
    {
        free_list_exec(data->commands);
        free(data->commands);
        data->commands = NULL;
        return (1);
    }
    get_cmd_path(*(data->commands), data);
    return (0);
}
