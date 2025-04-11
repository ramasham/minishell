/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:37:55 by rsham             #+#    #+#             */
/*   Updated: 2025/04/09 14:06:12 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void redirection_syntax_error(void)
{
    ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
}

void    parse_output(t_command *cmd, int *i)
{
    if (!cmd->full_cmd[*i + 1])
    {
        redirection_syntax_error();
        return;
    }
    handle_output_redirection(cmd, cmd->full_cmd[*i + 1],
        ft_strcmp(cmd->full_cmd[*i], ">>") == 0);
    *i += 2;
}

void    parse_input(t_command *cmd, int *i)
{
    if (!cmd->full_cmd[*i + 1])
    {
        redirection_syntax_error();
        return;
    }
    handle_input_redirection(cmd, cmd->full_cmd[*i + 1]);
    *i += 2;
}



void parse_redirection(t_command *cmd, t_data *data)
{
    int i;
    int len;

    len = 0;
    i = 0;
    if (!cmd || !cmd->full_cmd)
        return;
    while (cmd->full_cmd[i])
    {
        if (ft_strcmp(cmd->full_cmd[i], ">") == 0 || ft_strcmp(cmd->full_cmd[i], ">>") == 0)
            parse_output(cmd, &i);
        else if (ft_strcmp(cmd->full_cmd[i], "<") == 0)
            parse_input(cmd, &i);
        else if (ft_strcmp(cmd->full_cmd[i], "<<") == 0)
            parse_heredoc(cmd, &i, data);
        else
            cmd->full_cmd[len++] = cmd->full_cmd[i++];
    }
    cmd->full_cmd[len] = NULL;
}

