/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_full_cmd_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:46:52 by rsham             #+#    #+#             */
/*   Updated: 2025/04/23 19:36:03 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*create_and_initialize_cmd(void)
{
	t_command	*cmd;

	cmd = create_new_command();
	if (!cmd)
		return (NULL);
	cmd->full_cmd = NULL;
	return (cmd);
}

t_command	*create_new_command(void)
{
	t_command	*new_cmd;

	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->full_cmd = NULL;
	new_cmd->exe_cmd = NULL;
	new_cmd->full_path = NULL;
	new_cmd->next = NULL;
	// new_cmd->infile_fd = -1;
	// new_cmd->outfile_fd = -1;
	return (new_cmd);
}

void	add_command(t_data *data, t_command *new_cmd)
{
	t_command	**tmp;

	if (!new_cmd)
		return ;
	if (!data->commands)
	{
		data->commands = malloc(sizeof(t_command *));
		if (!data->commands)
		{
			free(new_cmd);
			return ;
		}
		*data->commands = NULL;
	}
	tmp = data->commands;
	if (!*tmp)
		*tmp = new_cmd;
	else
	{
		while ((*tmp)->next)
			tmp = &(*tmp)->next;
		(*tmp)->next = new_cmd;
	}
}
