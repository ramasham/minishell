/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:37:55 by rsham             #+#    #+#             */
/*   Updated: 2025/04/23 19:11:52 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirection_syntax_error(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
		2);
}

int	parse_output(t_data *data, t_command *cmd, int *i)
{
	char	*filename;

	if (!cmd->full_cmd[*i + 1])
	{
		redirection_syntax_error();
		return (1);
	}
	filename = remove_quotes(cmd->full_cmd[*i + 1]);
	if (!filename)
		return (1);
	if (handle_output_redirection(data, cmd, filename, cmd->append))
	{
		free(filename);
		return (1);
	}
	free(filename);
	*i += 2;
	return (0);
}

int	parse_input(t_data *data, t_command *cmd, int *i)
{
	char	*filename;

	if (!cmd->full_cmd[*i + 1])
	{
		redirection_syntax_error();
		return (1);
	}
	filename = remove_quotes(cmd->full_cmd[*i + 1]);
	if (!filename)
		return (1);
	if (handle_input_redirection(data, cmd, filename))
	{
		free(filename);
		return (1);
	}
	free(filename);
	*i += 2;
	return (0);
}

static int	handle_redirection(t_command *cmd, t_data *data, int *i)
{
	int	result;

	result = 0;
	if (ft_strcmp(cmd->full_cmd[*i], ">") == 0 || ft_strcmp(cmd->full_cmd[*i],
			">>") == 0)
	{
		if (ft_strcmp(cmd->full_cmd[*i], ">>") == 0)
			cmd->append = 1;
		result = parse_output(data, cmd, i);
	}
	else if (ft_strcmp(cmd->full_cmd[*i], "<") == 0)
		result = parse_input(data, cmd, i);
	else if (ft_strcmp(cmd->full_cmd[*i], "<<") == 0)
		result = parse_heredoc(cmd, i, data);
	if (result != 0)
		return (1);
	return (0);
}

int	parse_redirection(t_command *cmd, t_data *data)
{
	int	i;

	if (!cmd || !cmd->full_cmd)
		return (1);
	i = 0;
	while (cmd->full_cmd[i])
	{
		if (ft_strcmp(cmd->full_cmd[i], ">") == 0 || ft_strcmp(cmd->full_cmd[i],
				">>") == 0 || ft_strcmp(cmd->full_cmd[i], "<") == 0
			|| ft_strcmp(cmd->full_cmd[i], "<<") == 0)
		{
			if (handle_redirection(cmd, data, &i))
				return (1);
		}
		else
			i++;
	}
	return (0);
}
