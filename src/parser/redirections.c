/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:49:24 by rsham             #+#    #+#             */
/*   Updated: 2025/04/06 19:56:00 by rsham            ###   ########.fr       */
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

void    parse_input_redirection(t_command *cmd, int *i, int len)
{
    cmd->infile = 1;
    (*i)++;
    while (*i < len && is_space_str(cmd->full_cmd[*i]))
        (*i)++;
    if (*i < len)
        cmd->input_file = cmd->full_cmd[*i];
}


void    parse_output_redirection(t_command *cmd, int *i, int len)
{
    if (*i + 1 < len && cmd->full_cmd[*i + 1][0] == '>')
    {
        cmd->append = 1;
        (*i) += 2;
    }
    else
    {
        cmd->outfile = 1;
        (*i)++;
    }
    while (*i < len && is_space_str(cmd->full_cmd[*i]))
        (*i)++;
    if (*i < len)
        cmd->output_file = cmd->full_cmd[*i];
}

void parse_heredoc(t_command *cmd, int *i, int len)
{
    (*i)++;
    while (*i < len && is_space_str(cmd->full_cmd[*i]))
        (*i)++;
    if (*i < len)
    {
        cmd->heredoc_delim = cmd->full_cmd[*i];
        // printf("delim in parse = %c\n", cmd->heredeoc_delim[0]);
        if (cmd->heredoc_delim[0] == '"')
        {
            cmd->quoted = 1;
            cmd->heredoc_delim = ft_strremove(cmd->heredoc_delim, "\"");
        }
        // printf("delim in parse = %s\n", cmd->heredoc_delim);
        // printf("is q = %d\n", cmd->quoted);
        cmd->heredoc_fd = handle_heredoc(cmd);
    }
}

int input_redirection(t_command *cmd)
{
    int fd_in;

    if (cmd->input_file)
    {
        fd_in = open(cmd->input_file, O_RDONLY);
        if (fd_in == -1)
        {
            perror("Input redirection failed");
            return (-1);
        }
    
        if (dup2(fd_in, STDIN_FILENO) == -1)
        {
            perror("dup2 failed");
            close(fd_in);
            return (-1);
        }
        close(fd_in);
    }
    return (0);
}

int     output_redirection(t_command *cmd)
{
    int fd_out;
    
    if (cmd->output_file)
    {
        if (cmd->append)
            fd_out = open(cmd->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd_out = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out == -1)
        {
            perror("Output redirection failed");
            return (-1);
        }
        if (dup2(fd_out, STDOUT_FILENO) == -1)
        {
            perror("dup2 failed");
            close(fd_out);
            return (-1);
        }
        close(fd_out);
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

void parse_redirection(t_command *cmd, t_data *data)
{
    int i;
    int len;
    
    (void)data;
    i = 0;
    len  = count_tokens(cmd->full_cmd);
    while (i < len)
    {
        if (cmd->full_cmd[i][0] == '<' && i + 1 < len && cmd->full_cmd[i][1] == '<')
        {
            parse_heredoc(cmd, &i, len);
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
