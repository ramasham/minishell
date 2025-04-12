/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:48:26 by laburomm          #+#    #+#             */
/*   Updated: 2025/04/12 18:59:13 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int create_pipe_and_fork(int pipe_fd[2], pid_t *pid)
{
    if (pipe(pipe_fd) == -1)
        return(-1);
    *pid = fork();
    if (*pid == -1)
        return(-1);
    return(0);
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

int handle_heredoc_input(t_command *cmd, int pipe_fd[2], char *expanded, t_data *data)
{
    while (1)
    {
        if (g_exit_status == 130)
            return (1);
        cmd->heredoc_input = readline("> ");
        if (!cmd->heredoc_input)
            return (1);
        if (stop(cmd, cmd->heredoc_input))
        {
            free(cmd->heredoc_input);
            return (1);
        }
        write_to_pipe(cmd, pipe_fd, expanded, data);
        free(cmd->heredoc_input);
    }
    return (0);
}

int handle_parent_process(int pipe_fd[2], pid_t pid, int *status)
{
    signal(SIGINT, SIG_IGN);
    close(pipe_fd[1]);
    (void ) pid;
    wait(status);
    if (WIFSIGNALED(*status) || WIFEXITED(*status))
    {
        g_exit_status = WEXITSTATUS(*status);
        return (pipe_fd[0]);
    }
    signal(SIGINT, SIG_DFL);
    return (-1);
}

int handle_heredoc(t_command *cmd, t_data *data)
{
    int     pipe_fd[2];
    char    *expanded = NULL;
    int     status;
    pid_t   pid;

    if (create_pipe_and_fork(pipe_fd, &pid) == -1)
        return (-1);
    setup_heredoc_signals();
    if (pid == 0)
    {
        if (handle_heredoc_input(cmd, pipe_fd, expanded, data))
        {
            close(pipe_fd[1]);
            exit(g_exit_status);
        }
    }
    else
        return (handle_parent_process(pipe_fd, pid, &status));    
    return(0);
}
