/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:48:20 by laburomm          #+#    #+#             */
/*   Updated: 2025/04/13 17:41:31 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int stop(t_command *cmd, char *line)
{
    int line_len;
    int delim_len;

    if (!line || !cmd->heredoc_delim)
        return (1);
    line_len = ft_strlen(line);
    delim_len = ft_strlen(cmd->heredoc_delim);
    if (ft_strcmp(line, cmd->heredoc_delim) == 0 && (line_len == delim_len))
        return (1);
    return (0);
}

void cleanup_heredoc(t_command *cmd)
{
    if (cmd->heredoc_fd != -1)
    {
        printf("%d wdawdawdaw\n", cmd->heredoc_fd);        
        close(cmd->heredoc_fd);
    }
    if (cmd->heredoc_delim)
        free(cmd->heredoc_delim);
    cmd->heredoc_fd = -1;
    cmd->heredoc_delim = NULL;
}

