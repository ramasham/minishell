/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:48:20 by laburomm          #+#    #+#             */
/*   Updated: 2025/04/09 11:34:38 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void cleanup_heredoc(t_command *cmd)
{
    if (cmd->heredoc_fd != -1)
        close(cmd->heredoc_fd);
    if (cmd->heredoc_delim)
        free(cmd->heredoc_delim);
    cmd->heredoc_fd = -1;
    cmd->heredoc_delim = NULL;
}

