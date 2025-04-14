/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 01:05:37 by rsham             #+#    #+#             */
/*   Updated: 2025/04/14 19:59:13 by rsham            ###   ########.fr       */
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
		if (!curr->exe_cmd || !curr->exe_cmd[0])
		{
			if (prev)
				prev->next = next;
			else
				*cmd_list = next;
            // if (curr->skip == 0)
            // {
            //     printf("skip\n");
            //     cleanup_redirections(curr);
            // }
            if (curr->exe_cmd)
            {
                int i = 0;
                while (curr->exe_cmd[i])
                {
                    free(curr->exe_cmd[i]);
                    i++;
                }
                free(curr->exe_cmd);
            }
			free(curr);
		}
		else
			prev = curr;
		curr = next;
	}
}

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
    cmd->exe_cmd = malloc((count + 1) * sizeof(char *));
    if (!cmd->exe_cmd)
        return (1);
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
    t_command *cmd;
    int cmd_num;
    int redirection_error;

    get_command(data, *(data->node));
    remove_quotes_from_command(*data->commands);
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
        if (create_exec_cmd(data, cmd))
            return (1);
        cmd = cmd->next;
    }
    if (redirection_error)
    {
        free_list_exec(data->commands);
        free(data->commands);
        data->commands = NULL;
        return (1);
    }
    remove_empty_commands(data->commands);
    cmd_num = count_commands(*data->commands);
    if (cmd_num <= 0)
        return (1);
    get_cmd_path(*(data->commands), data);
    return (0);
}
