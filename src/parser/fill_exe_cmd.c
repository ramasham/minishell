/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_exe_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:15:58 by rsham             #+#    #+#             */
/*   Updated: 2025/04/23 13:45:52 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char *s)
{
	if (ft_strchr(s, '\'') || ft_strchr(s, '"'))
		return (0);
	return (!ft_strcmp(s, "<") || !ft_strcmp(s, ">")
		|| !ft_strcmp(s, ">>") || !ft_strcmp(s, "<<"));
}

static int	count_non_operators(char **full_cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (full_cmd[i])
	{
		if (is_operator(full_cmd[i]))
		{
			i++;
			if (full_cmd[i])
				i++;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

static int	handle_empty_cmd(t_data *data, t_command *cmd)
{
	(void)data;
	int	i;

	i = 0;
	// data->empty = 1;
	cleanup_redirections(cmd);
	while (cmd->full_cmd[i])
	{
		free(cmd->full_cmd[i]);
		i++;
	}
	free(cmd->full_cmd);
	cmd->full_cmd = NULL;
	return (0);
}


static void	fill_exe_cmd(t_command *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->full_cmd[i])
	{
		if (is_operator(cmd->full_cmd[i]))
		{
			i++;
			if (cmd->full_cmd[i])
				i++;
		}
		else
		{
			cmd->exe_cmd[j] = ft_strdup(cmd->full_cmd[i]);
			j++;
			i++;
		}
	}
	cmd->exe_cmd[j] = NULL;
}

int	create_exec_cmd(t_data *data, t_command *cmd)
{
	int	count;
	int	i;

	i = 0;
	(void)data;
	if (!cmd->full_cmd)
		return (1);
	count = count_non_operators(cmd->full_cmd);
	if (count == 0)
	{
		if (!cmd->exe_cmd || !cmd->exe_cmd[0])
			return (handle_empty_cmd(data, cmd));
	}
	cmd->exe_cmd = malloc((count + 1) * sizeof(char *));
	if (!cmd->exe_cmd)
		return (1);
	fill_exe_cmd(cmd);
	while (cmd->full_cmd[i])
	{
		free(cmd->full_cmd[i]);
		i++;
	}
	free(cmd->full_cmd);
	cmd->full_cmd = NULL;
	return (0);
}
