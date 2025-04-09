/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:49:24 by rsham             #+#    #+#             */
/*   Updated: 2025/04/09 18:49:34 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_output_redirection(t_command *cmd, char *filename, int append)
{
    int fd;
    int flags;

    flags = O_WRONLY | O_CREAT;
    if (append)
        flags |= O_APPEND;
    else
        flags |= O_TRUNC;
    fd = open(filename, flags, 0644);
    if (fd == -1)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(filename, 2);
        ft_putstr_fd(": ", 2);
        perror("");
        return (1);
    }
    if (cmd->outfile_fd != STDOUT_FILENO)
        close(cmd->outfile_fd);
    cmd->outfile_fd = fd;
    cmd->output_file = filename;
    return (0);
}

int handle_input_redirection(t_command *cmd, char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(filename, 2);
        ft_putstr_fd(": ", 2);
        perror("");
        return (1);
    }
    if (cmd->infile_fd != STDIN_FILENO)
        close(cmd->infile_fd);
    cmd->infile_fd = fd;
    cmd->input_file = filename;
    return (0);
}

int setup_redirections(t_command *cmd)
{
    if (cmd->infile_fd != STDIN_FILENO)
    {
        if (dup2(cmd->infile_fd, STDIN_FILENO) == -1)
            return (1);
        close(cmd->infile_fd);
    }
    if (cmd->outfile_fd != STDOUT_FILENO)
    {
        if (dup2(cmd->outfile_fd, STDOUT_FILENO) == -1)
            return (1);
        close(cmd->outfile_fd);
    }
    return (0);
}

void cleanup_redirections(t_command *cmd)
{
    if (cmd->infile_fd != STDIN_FILENO)
        close(cmd->infile_fd);
    if (cmd->outfile_fd != STDOUT_FILENO)
        close(cmd->outfile_fd);
    if (cmd->heredoc_fd != -1)
        close(cmd->heredoc_fd);
    if (cmd->heredoc_delim)
        free(cmd->heredoc_delim);
    cmd->infile_fd = STDIN_FILENO;
    cmd->outfile_fd = STDOUT_FILENO;
    cmd->heredoc_fd = -1;
    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->heredoc_delim = NULL;
}

