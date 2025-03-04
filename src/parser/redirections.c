/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:49:24 by rsham             #+#    #+#             */
/*   Updated: 2025/03/04 00:36:33 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_redirections(t_command *cmd)
{
    int i;

    i = 0;
    cmd->infile = STDIN_FILENO;
    cmd->outfile = STDOUT_FILENO;
    while (cmd->full_cmd[i])
    {
        if (ft_strcmp(cmd->full_cmd[i], ">") == 0 || ft_strcmp(cmd->full_cmd[i], ">>") == 0)
        {
            cmd->outfile = handle_output_redirection(cmd->full_cmd[i], cmd->full_cmd[i + 1]);
            cmd->full_cmd[i] = NULL;
            cmd->full_cmd[i + 1] = NULL;
        }
        else if (ft_strcmp(cmd->full_cmd[i], "<") == 0)
        {
            cmd->infile = handle_input_redirection(cmd->full_cmd[i + 1]);
            cmd->full_cmd[i] = NULL;
            cmd->full_cmd[i + 1] = NULL;
        }
        else if (ft_strcmp(cmd->full_cmd[i], "<<") == 0)
        {
            cmd->heredoc_fd = handle_heredoc(cmd->full_cmd[i + 1]);
            cmd->infile = cmd->heredoc_fd;
            cmd->full_cmd[i] = NULL;
            cmd->full_cmd[i + 1] = NULL;
        }
        i++;
    }
}

void set_redi(t_command *cmd)
{
    handle_redirections(cmd);
    
    if (cmd->infile != STDIN_FILENO)
    {
        dup2(cmd->infile, STDIN_FILENO);
        close(cmd->infile);
    }
    if (cmd->outfile != STDOUT_FILENO)
    {
        dup2(cmd->outfile, STDOUT_FILENO);
        close(cmd->outfile);
    }
}

int handle_output_redirection(char *operator, char *filename)
{
    int fd;
    int flags;

    flags = 0;
    // printf("file = %s\n",filename);
    if (!filename)
    {
        ft_putstr_fd("no file\n", 2);
        return (-1);
    }
    if (ft_strcmp(operator, ">") == 0)
        flags = O_WRONLY | O_CREAT | O_TRUNC;
    else if (ft_strcmp(operator, ">>") == 0)
        flags = O_WRONLY | O_CREAT | O_APPEND;
    else
    {
        ft_putstr_fd("Invalid redirection operator\n", 2);
        return (-1);
    }
    fd = open(filename, flags, 0644);
    if (fd == -1)
    {
        perror("Output redirection failed");
    }
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
