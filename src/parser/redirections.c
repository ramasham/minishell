/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:49:24 by rsham             #+#    #+#             */
/*   Updated: 2025/02/25 11:26:18 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    handle_redirections(t_command *cmd, t_node *tokens)
{
    t_node *current;

    current = tokens;
    while (current)
    {
        if (ft_strcmp(current->content, D_REDIR_OUT) == 0 || ft_strcmp(current->content, D_APPEND) == 0)
            cmd->outfile = handle_output_redirection(current->content, current->next->content);
        else if (ft_strcmp(current->content, D_REDIR_IN) == 0)
            cmd->infile = handle_input_redirection(current->next->content);
        // handle here_doc
        current = current->next;
    }
}

int handle_output_redirection(char *operator, char *filename)
{
    int fd;

    if (ft_strcmp(operator, D_REDIR_OUT) == 0)
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (ft_strcmp(operator, D_APPEND) == 0)
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
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