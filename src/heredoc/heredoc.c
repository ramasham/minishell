/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:48:26 by laburomm          #+#    #+#             */
/*   Updated: 2025/04/10 16:47:16 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int stop(t_command *cmd, char *line)
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

void    write_to_pipe(t_command *cmd, int *pipe_fd, char *expanded, t_data *data)
{
    if (!cmd->quoted)
    {
        expanded = expand_heredoc_content(cmd->heredoc_input, data);
        if (expanded)
        {
            write(pipe_fd[1], expanded, ft_strlen(expanded));
            write(pipe_fd[1], "\n", 1);
            free(expanded);
        }
    }
    else
    {
        write(pipe_fd[1], cmd->heredoc_input, ft_strlen(cmd->heredoc_input));
        write(pipe_fd[1], "\n", 1);
    }
}


int handle_heredoc(t_command *cmd, t_data *data)
{
    int     pipe_fd[2];
    char    *expanded;

    expanded = NULL;
    if (pipe(pipe_fd) == -1)
        return (-1);
    setup_heredoc_signals();
    while (1)
    {
        cmd->heredoc_input = readline("> ");
        if (!cmd->heredoc_input)
            break;
        if (stop(cmd, cmd->heredoc_input))
        {
            free(cmd->heredoc_input);
            break;
        }
        write_to_pipe(cmd, pipe_fd, expanded, data);
        free(cmd->heredoc_input);
    }
    close(pipe_fd[1]);
    return (pipe_fd[0]);
}

