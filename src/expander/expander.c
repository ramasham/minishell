/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:33:44 by laburomm          #+#    #+#             */
/*   Updated: 2025/04/17 19:29:45 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_exit_status(t_node *current, t_data *data)
{
	char	*exit_status;

	exit_status = ft_itoa(data->last_exit_status);
	if (!exit_status)
		return (1);
	free(current->content);
	current->content = exit_status;
	return (0);
}

int	process_node(t_node *current, t_data *data)
{
	int	i;
	int	in_single;
	int	in_double;

	if (!current->content)
		return (1);
	i = -1;
	in_single = 0;
	in_double = 0;
	while (current->content[++i])
	{
		handle_quotes(current->content[i], &in_single, &in_double);
		if (!in_single && current->content[i] == '$' && current->content[i + 1])
		{
			if (current->content[i + 1] == '?')
				return (handle_exit_status(current, data));
			else if (process_env_if_needed(current, &i, in_single, data))
				return (1);
		}
	}
	return (0);
}

int	detect_env(t_data *data)
{
	t_node	*current;

	current = (*data->node);
	while (current)
	{
		if (!current->content || !*(current->content))
			return (1);
		if (process_node(current, data))
			return (1);
		current = current->next;
	}
	return (0);
}

int	expander(t_data *data)
{
	if (detect_env(data))
		return (1);
	return (0);
}
