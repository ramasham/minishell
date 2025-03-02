/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:49:24 by rsham             #+#    #+#             */
/*   Updated: 2025/03/02 16:52:28 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handle_redirections(t_command *cmd)
{
    int i;
    int fd;
    
    fd = -1;
    i = -1;
    while (cmd->full_cmd[++i])
    {
        if (ft_strcmp(cmd->full_cmd[i], ">") == 0 || ft_strcmp(cmd->full_cmd[i] , ">>") == 0)
            fd = handle_output_redirection(cmd->full_cmd[i], cmd->full_cmd[i + 1]);

        else if (ft_strcmp(cmd->full_cmd[i], "<") == 0)
            fd = handle_input_redirection(cmd->full_cmd[i + 1]);
        if (fd == -1)
        {
            perror("open");
            exit(1);
        }
        // else if (ft_strcmp(cmd->full_cmd[i], "<<") == 0)
		// 	fd = handle_heredoc_redirection(cmd->full_cmd[i + 1]);
        if (fd != -1)
        {
            if (ft_strcmp(cmd->full_cmd[i], "<") == 0 || ft_strcmp(cmd->full_cmd[i], "<<") == 0)
                dup2(fd, STDIN_FILENO);
            else
                dup2(fd, STDOUT_FILENO);
            close(fd);
        }
    }
}


int handle_output_redirection(char *operator, char *filename)
{
    int fd;
    int flags;
    if (!filename)
    {
        ft_putstr_fd("no file\n", 2);
        return (-1);
    }
    flags = O_WRONLY | O_CREAT;
    if (ft_strcmp(operator, ">") == 0)
        flags |= O_TRUNC;
    else if (ft_strcmp(operator, ">>") == 0)
        flags |= O_APPEND;
    fd = open(filename, flags, 0644);
    if (fd == -1)
        perror("Output redirection failed");
    return (fd);
}

int handle_input_redirection(char  *filename)
{
    int fd;

    if (!filename)
    {
        ft_putstr_fd("no file\n", 2);
        return (-1);
    }
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        perror("Input redirection failed");
    return (fd);
}