/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:49:24 by rsham             #+#    #+#             */
/*   Updated: 2025/04/08 19:58:17 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void shift_left(char **full_cmd, int start, int len)
{
    while (start < len - 2)
    {
        full_cmd[start] = full_cmd[start + 2];
        start++;
    }
    full_cmd[start] = NULL;
}

void parse_input_redirection(t_command *cmd, int *i, int len)
{
    (*i)++;
    while (*i < len && is_space_str(cmd->full_cmd[*i]))
        (*i)++;

    if (*i < len)
    {
        cmd->input_file = cmd->full_cmd[*i];
        int fd = open(cmd->input_file, O_RDONLY);
        if (fd == -1)
        {
            perror("Input redirection failed");
            return;
        }
        if (cmd->last_infile_fd != -1)
            close(cmd->last_infile_fd);
        cmd->last_infile_fd = fd;
    }
}


void parse_output_redirection(t_command *cmd, int *i, int len)
{
    int fd;

    cmd->append = (cmd->full_cmd[*i + 1] && cmd->full_cmd[*i + 1][0] == '>');
    if (cmd->append)
        (*i) += 2;
    else
        (*i)++;

    while (*i < len && is_space_str(cmd->full_cmd[*i]))
        (*i)++;

    if (*i < len)
    {
        char *file = cmd->full_cmd[*i];
        if (cmd->append)
            fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

        if (fd == -1)
        {
            perror("Output redirection failed");
            return;
        }

        if (cmd->outfile_count < 10)
        {
            cmd->output_files[cmd->outfile_count] = file;
            cmd->output_fds[cmd->outfile_count] = fd;
            cmd->outfile_count++;
        }
    }
}


void parse_heredoc(t_command *cmd, int *i, int len)
{
    (*i)++;
    while (*i < len && is_space_str(cmd->full_cmd[*i]))
        (*i)++;
    if (*i < len)
    {
        cmd->heredoc_delim = cmd->full_cmd[*i];
        if (cmd->heredoc_delim[0] == '"')
        {
            cmd->quoted = 1;
            cmd->heredoc_delim = ft_strremove(cmd->heredoc_delim, "\"");
        }
        cmd->heredoc_fd = handle_heredoc(cmd);
    }
}
int output_redirection(t_command *cmd)
{
    if (cmd->outfile_count > 0)
    {
        int fd = cmd->output_fds[cmd->outfile_count - 1];
        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            perror("dup2 failed");
            close(fd);
            return (-1);
        }
        // Close all other output fds
        for (int j = 0; j < cmd->outfile_count; j++)
        {
            if (j != cmd->outfile_count - 1)
                close(cmd->output_fds[j]);
        }
    }
    return (0);
}


int count_tokens(char **full_cmd)
{
    int count = 0;

    while (full_cmd && full_cmd[count])
        count++;
    return (count);
}

void parse_redirection(t_command *cmd)
{
    int i;
    int len;

    i = 0;
    len  = count_tokens(cmd->full_cmd);
    while (i < len)
    {
        if (cmd->full_cmd[i][0] == '<' && i + 1 < len && cmd->full_cmd[i][1] == '<')
            parse_heredoc(cmd, &i, len); // close prev fd from last herdoc (if any)
        else
            i++;
    }
    i = 0
    while (i < len)
    {
        if (cmd->full_cmd[i][0] == '<' && i + 1 < len && cmd->full_cmd[i][1] == '<')
        {
            cmd->last_infile_fd = cmd->heredoc_fd;
            shift_left(cmd->full_cmd, i - 1, len);
            len -= 2;
        }
        else if (cmd->full_cmd[i][0] == '<')
        {
            parse_input_redirection(cmd, &i, len);
            shift_left(cmd->full_cmd, i - 1, len);
            len -= 2;
        }
        else if (cmd->full_cmd[i][0] == '>')
        {
            parse_output_redirection(cmd, &i, len);
            shift_left(cmd->full_cmd, i - 1, len);
            len -= 2;
        }
        else
            i++;
    }
}
