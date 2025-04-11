/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:36:34 by rsham             #+#    #+#             */
/*   Updated: 2025/04/09 14:21:38 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    heredoc_delim(t_command *cmd, int *i)
{
    char *tmp;
    
    cmd->heredoc_delim = ft_strdup(cmd->full_cmd[*i + 1]);
    if (!cmd->heredoc_delim)
        return;
    if (cmd->heredoc_delim[0] == '"')
    {
        cmd->quoted = 1;
        tmp = ft_strremove(cmd->heredoc_delim, "\"");
        if (tmp)
        {
            free(cmd->heredoc_delim);
            cmd->heredoc_delim = tmp;
        }
    }
    else if (cmd->heredoc_delim[0] == '\'')
    {
        tmp = ft_strremove(cmd->heredoc_delim, "'");
        if (tmp)
        {
            free(cmd->heredoc_delim);
            cmd->heredoc_delim = tmp;
        }
    }
}

void parse_heredoc(t_command *cmd, int *i, t_data *data)
{
    if (!cmd->full_cmd[*i + 1])
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
        return;
    }
    cmd->heredoc_delim = ft_strdup(cmd->full_cmd[*i + 1]);
    if (!cmd->heredoc_delim)
        return;
    heredoc_delim(cmd, i);
    cmd->heredoc_fd = handle_heredoc(cmd, data);
    if (cmd->heredoc_fd == -1)
    {
        free(cmd->heredoc_delim);
        cmd->heredoc_delim = NULL;
        return;
    }
    if (cmd->infile_fd != STDIN_FILENO)
        close(cmd->infile_fd);
    cmd->infile_fd = cmd->heredoc_fd;
    *i += 2;
}
