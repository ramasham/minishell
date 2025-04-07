/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:48:26 by laburomm          #+#    #+#             */
/*   Updated: 2025/04/07 18:58:21 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int stop(t_command *cmd, char *line)
{
    int line_len;
    int delim_len;

    line_len = ft_strlen(line);
    delim_len = ft_strlen(cmd->heredoc_delim);
    if (ft_strcmp(line, cmd->heredoc_delim) == 0 && (line_len == delim_len))
        return (1);
    return (0);
}

// int expansion_process(char *line)
// {
    
// }

int handle_heredoc(t_command *cmd)
{
    int     pipe_fd[2];
    
    if (pipe(pipe_fd) == -1)
        return (-1);
    while (1)
    {
        cmd->heredoc_input = readline("> ");
        if (!cmd->heredoc_input)
            break;
        // if (cmd->quoted)
        //     expansion_process(cmd->heredoc_input);
        if (stop(cmd, cmd->heredoc_input))
        {
            free(cmd->heredoc_input);
            break;
        }
        write(pipe_fd[1],cmd->heredoc_input, ft_strlen(cmd->heredoc_input));
        write(pipe_fd[1], "\n", 1);
        free(cmd->heredoc_input);
    }
    close(pipe_fd[1]);
    return (pipe_fd[0]);
}

