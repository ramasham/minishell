/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:37:55 by rsham             #+#    #+#             */
/*   Updated: 2025/04/10 20:01:10 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void redirection_syntax_error(void)
{
    ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
}

int    parse_output(t_data *data, t_command *cmd, int *i)
{
    if (!cmd->full_cmd[*i + 1])
    {
        redirection_syntax_error();
        return(1);
    }
    if (handle_output_redirection(data, cmd, cmd->full_cmd[*i + 1],
        ft_strcmp(cmd->full_cmd[*i], ">>") == 0))
    {
        // return (1);        
    }
    *i += 2;
    return(0);
}

int    parse_input(t_command *cmd, int *i)
{
    if (!cmd->full_cmd[*i + 1])
    {
        redirection_syntax_error();
        return (1);
    }
    if (handle_input_redirection(cmd, cmd->full_cmd[*i + 1]))
    {
        // return (1);
    }
    *i += 2;
    return(0);
}

void	remove_empty_commands(t_command **cmd_list)
{
	t_command *prev;
	t_command *curr;
	t_command *next;
    
    prev = NULL;
    curr = *cmd_list;
	while (curr)
	{
		next = curr->next;
		if (!curr->full_cmd || !curr->full_cmd[0])
		{
			if (prev)
				prev->next = next;
			else
				*cmd_list = next;
			free(curr->full_cmd);
			free(curr);
		}
		else
			prev = curr;
		curr = next;
	}
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
        {
            data->redirection = 1;
            parse_output(data, cmd, &i);
            free(cmd->full_cmd[i - 2]);
            free(cmd->full_cmd[i - 1]);
        }
        else if (ft_strcmp(cmd->full_cmd[i], "<") == 0)
        {
            data->redirection = 1;
            parse_input(cmd, &i);
            free(cmd->full_cmd[i - 2]);
            free(cmd->full_cmd[i - 1]);
            
        }
        else if (ft_strcmp(cmd->full_cmd[i], "<<") == 0)
        {
            data->redirection = 1;
            parse_heredoc(cmd, &i, data);
            free(cmd->full_cmd[i - 2]);// remove <<     
            free(cmd->full_cmd[i - 1]); // remvove 1
            // cleanup_heredoc(cmd);
        }
        else
            cmd->full_cmd[len++] = cmd->full_cmd[i++];
    }
    cmd->full_cmd[len] = NULL;
}

