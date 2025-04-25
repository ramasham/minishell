/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_full_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:34:52 by rsham             #+#    #+#             */
/*   Updated: 2025/04/16 14:31:54 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args_before_pipe(t_node *current)
{
	int	arg_count;

	arg_count = 0;
	while (current && ft_strcmp(current->content, "|") != 0)
	{
		arg_count++;
		current = current->next;
	}
	return (arg_count);
}

void	fill_full_cmd(t_node **current, t_command *new_cmd, int arg_count)
{
	int	i;

	i = 0;
	new_cmd->full_cmd = malloc(sizeof(char *) * (arg_count + 1));
	if (!new_cmd->full_cmd)
	{
		free(new_cmd);
		return ;
	}
	while (*current && ft_strcmp((*current)->content, "|") != 0)
	{
		new_cmd->full_cmd[i] = ft_strdup((*current)->content);
		if (!new_cmd->full_cmd[i])
		{
			while (i-- > 0)
				free(new_cmd->full_cmd[i]);
			free(new_cmd->full_cmd);
			new_cmd->full_cmd = NULL;
			return ;
		}
		*current = (*current)->next;
		i++;
	}
	new_cmd->full_cmd[i] = NULL;
}

int	process_current_cmd(t_node **current, t_command *new_cmd)
{
	int	arg_count;

	arg_count = count_args_before_pipe(*current);
	fill_full_cmd(current, new_cmd, arg_count);
	if (!new_cmd->full_cmd)
		return (-1);
	return (0);
}

static void	clean_cmd(t_data *data)
{
	if (data->commands)
	{
		free_list_cmd(data->commands);
		free(data->commands);
		data->commands = NULL;
	}
}

void	get_command(t_data *node_lst, t_node *current)
{
	t_command	*new_cmd;

	while (current)
	{
		new_cmd = create_and_initialize_cmd();
		if (!new_cmd)
		{
			clean_cmd(node_lst);
			return ;
		}
		if (process_current_cmd(&current, new_cmd) == -1)
		{
			clean_cmd(node_lst);
			return ;
		}
		add_command(node_lst, new_cmd);
		if (current && ft_strcmp(current->content, "|") == 0)
			current = current->next;
	}
	free_list(node_lst->node);
	free(node_lst->node);
	node_lst->node = NULL;
}
