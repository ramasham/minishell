/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:49:24 by rsham             #+#    #+#             */
/*   Updated: 2025/03/01 17:43:16 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handle_redirection(t_command *cmd)
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
        else if (ft_strcmp(cmd->full_cmd[i], "<<") == 0)
			fd = handle_heredoc_redirection(cmd->full_cmd[i + 1]);
        if (fd == -1)
            exit(1);
        if (fd > 0)
        {
            if (ft_strcmp(cmd->full_cmd[i], "<") == 0 || ft_strcmp(cmd->full_cmd[i], "<<") == 0)
                dup2(fd, STDIN_FILENO);
            else
                dup2(fd, STDOUT_FILENO);
            close(fd);
            cmd->full_cmd[i] = NULL;
        }
    }
}


// // Function to handle input/output redirection
// void handle_redirections(t_command *cmd, t_data *data) {
//     int out_fd = -1;
//     (void)data;
//     // Check for output redirection
//     for (int i = 0; cmd->full_cmd[i]; i++) {
//         if (strcmp(cmd->full_cmd[i], ">") == 0) {
//             // If we find '>', open the file for writing
//             out_fd = open(cmd->full_cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//             if (out_fd == -1) {
//                 perror("open");
//                 exit(1);
//             }
//             cmd->full_cmd[i] = NULL;  // Nullify the redirection part
//             break;
//         }
//     }

//     // If we have a valid output file descriptor, redirect the output
//     if (out_fd != -1) {
//         dup2(out_fd, STDOUT_FILENO);  // Redirect standard output to the file
//         close(out_fd);  // Close the file descriptor after redirection
//     }
// }

// void    handle_redirections(t_command *cmd, t_node *tokens)
// {
//     t_node *current;

//     current = tokens;
//     while (current)
//     {
//         if (ft_strcmp(current->content, D_REDIR_OUT) == 0 || ft_strcmp(current->content, D_APPEND) == 0)
//             cmd->outfile = handle_output_redirection(current->content, current->next->content);
//         else if (ft_strcmp(current->content, D_REDIR_IN) == 0)
//             cmd->infile = handle_input_redirection(current->next->content);
//         // handle here_doc
//         current = current->next;
//     }
// }

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
    else if (ft_strcmp(operator, "<<") == 0)
        flags |= O_APPEND;
    else
        return (-1);
    if (fd == -1)
        perror("Output redirection failed");
    return (fd);
}

int handle_input_redirection(char  *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Input redirection failed");
    }
    return (fd);
}