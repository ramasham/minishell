/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 02:00:04 by rsham             #+#    #+#             */
/*   Updated: 2025/03/06 23:19:13 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_heredoc(t_data *data, char *delimiter)
{
    int pipe_fd[2];
    char    *line;

    if (!delimiter)
        return (-1);
    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        return (-1);
    }
    while (1)
    {
        ft_putstr_fd("> ", 1);
        line = get_next_line(STDIN_FILENO);
        if (!line)
            break;
        if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0 && (ft_strlen(line) - 1 == ft_strlen(delimiter)))
        {
            free (line);
            break;
        }
        write (pipe_fd[1], line, ft_strlen(line));
    }
    close(pipe_fd[1]);
    return (pipe_fd[0]);
}
