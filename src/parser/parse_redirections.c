/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:37:55 by rsham             #+#    #+#             */
/*   Updated: 2025/04/13 18:25:40 by rsham            ###   ########.fr       */
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
    if (handle_output_redirection(data, cmd, cmd->full_cmd[*i + 1], cmd->append))
        return (1);
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
        return (1);
    *i += 2;
    return(0);
}


static int	handle_redirection(t_command *cmd, t_data *data, int *i)
{
    int result;

    result = 0;
	if (ft_strcmp(cmd->full_cmd[*i], ">") == 0 || ft_strcmp(cmd->full_cmd[*i], ">>") == 0)
    {
        if (ft_strcmp(cmd->full_cmd[*i], ">>") == 0)
            cmd->append = 1;
		result = parse_output(data, cmd, i);
    }
	else if (ft_strcmp(cmd->full_cmd[*i], "<") == 0)
		result = parse_input(cmd, i);
	else if (ft_strcmp(cmd->full_cmd[*i], "<<") == 0)
		result = parse_heredoc(cmd, i, data);
    if (result != 0)
        return (1);
    free(cmd->full_cmd[*i - 2]);
	cmd->full_cmd[*i - 2] = NULL;
	free(cmd->full_cmd[*i - 1]);
	cmd->full_cmd[*i - 1] = NULL;
    return (0);
}

int	parse_redirection(t_command *cmd, t_data *data)
{
	int	i;
	int	len;

	if (!cmd || !cmd->full_cmd)
		return(1);
	i = 0;
	len = 0;
	while (cmd->full_cmd[i])
	{
		if (ft_strcmp(cmd->full_cmd[i], ">") == 0 || ft_strcmp(cmd->full_cmd[i], ">>") == 0
			|| ft_strcmp(cmd->full_cmd[i], "<") == 0 || ft_strcmp(cmd->full_cmd[i], "<<") == 0)
        {
            if (handle_redirection(cmd, data, &i))
            {
                return(1);
            }
        }
		else
			cmd->full_cmd[len++] = cmd->full_cmd[i++];
	}
	cmd->full_cmd[len] = NULL;
	if (len == 0)
		cmd->skip = 1;
    return (0);
}

