/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:49:24 by rsham             #+#    #+#             */
/*   Updated: 2025/03/23 02:26:24 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_redirections(t_command *cmd, t_data *data)
{
    int i;
    int j;

    i = 0;
    cmd->infile = STDIN_FILENO;
    cmd->outfile = STDOUT_FILENO;
    cmd->heredoc_fd = -1;

    while (cmd->full_cmd[i])
    {
        if (ft_strcmp(cmd->full_cmd[i], ">") == 0 || ft_strcmp(cmd->full_cmd[i], ">>") == 0)
        {
            if (!cmd->full_cmd[i + 1])
            {
                ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n", 2);
                return;
            }
            cmd->outfile = handle_output_redirection(cmd->full_cmd[i], cmd->full_cmd[i + 1]);
            if (cmd->outfile == -1)
                return;
            cmd->full_cmd[i] = NULL;
            cmd->full_cmd[i + 1] = NULL;
            i += 2;
        }
        else if (ft_strcmp(cmd->full_cmd[i], "<") == 0)
        {
            if (!cmd->full_cmd[i + 1])
            {
                ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n", 2);
                return;
            }
            cmd->infile = handle_input_redirection(cmd->full_cmd[i + 1]);
            if (cmd->infile == -1)
                return;
            cmd->full_cmd[i] = NULL;
            cmd->full_cmd[i + 1] = NULL;
            i += 2;
        }
        else if (ft_strcmp(cmd->full_cmd[i], "<<") == 0)
        {
            if (!cmd->full_cmd[i + 1])
            {
                ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n", 2);
                return;
            }
            cmd->heredoc_fd = handle_heredoc(cmd->full_cmd[i + 1], data);
            if (cmd->heredoc_fd == -1)
                return;
            cmd->infile = cmd->heredoc_fd;
            cmd->full_cmd[i] = NULL;
            cmd->full_cmd[i + 1] = NULL;
            i += 2;
        }
        else
        {
            i++;
        }
    }

    // Clean up NULL entries in full_cmd
    i = 0;
    j = 0;
    while (cmd->full_cmd[i])
    {
        if (cmd->full_cmd[i] != NULL)
        {
            if (i != j)
                cmd->full_cmd[j] = cmd->full_cmd[i];
            j++;
        }
        i++;
    }
    cmd->full_cmd[j] = NULL;
}

// void handle_redirections(t_command *cmd, t_data *data)
// {
//     int i;

//     i = 0;
//     cmd->infile = STDIN_FILENO;
//     cmd->outfile = STDOUT_FILENO;

//     while (cmd->full_cmd[i])
//     {
//         if (ft_strcmp(cmd->full_cmd[i], ">") == 0 || ft_strcmp(cmd->full_cmd[i], ">>") == 0)
//         {
//             cmd->outfile = handle_output_redirection(cmd->full_cmd[i], cmd->full_cmd[i + 1]);
//             if (cmd->outfile == -1)
//                 return;
//             cmd->full_cmd[i] = NULL;
//             cmd->full_cmd[i + 1] = NULL;
//             i += 2;
//         }
//         else if (ft_strcmp(cmd->full_cmd[i], "<") == 0)
//         {
//             cmd->infile = handle_input_redirection(cmd->full_cmd[i + 1]);
//             if (cmd->infile == -1)
//                 return;
//             cmd->full_cmd[i] = NULL;
//             cmd->full_cmd[i + 1] = NULL;
//             i += 2;
//         }
//         else if (ft_strcmp(cmd->full_cmd[i], "<<") == 0)
//         {
//             cmd->heredoc_fd = handle_heredoc(cmd->full_cmd[i + 1], data);
//             cmd->infile = cmd->heredoc_fd;
//             cmd->full_cmd[i] = NULL;
//             cmd->full_cmd[i + 1] = NULL;
//             i += 2;
//         }
//         else
//         {
//             i++;
//         }
//     }
// }

void set_redi(t_command *cmd, t_data *data)
{  
    handle_redirections(cmd, data);

    // Handle input redirection
    if (cmd->infile != STDIN_FILENO)
    {
        if (dup2(cmd->infile, STDIN_FILENO) == -1)
        {
            ft_putstr_fd("Error duplicating input file descriptor\n", 2);
            return;
        }
        close(cmd->infile);
    }

    // Handle output redirection
    if (cmd->outfile != STDOUT_FILENO)
    {
        if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
        {
            ft_putstr_fd("Error duplicating output file descriptor\n", 2);
            return;
        }
        close(cmd->outfile);
    }
}


// void set_redi(t_command *cmd, t_data *data)
// {
//     handle_redirections(cmd, data);
    
//     if (cmd->infile != STDIN_FILENO)
//     {
//         dup2(cmd->infile, STDIN_FILENO);
//         close(cmd->infile);
//     }
//     if (cmd->outfile != STDOUT_FILENO)
//     {
//         dup2(cmd->outfile, STDOUT_FILENO);
//         close(cmd->outfile);
//     }
// }

int handle_output_redirection(char *operator, char *filename)
{
    int fd;
    int flags;

    flags = 0;
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
        ft_putstr_fd("Permission denied\n", 2);
        return (-1);
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
    {
        ft_putstr_fd("No such file or directory\n", 2);
        return (-1);
    }
    return (fd);
}
