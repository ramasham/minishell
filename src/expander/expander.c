/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:33:44 by laburomm          #+#    #+#             */
/*   Updated: 2025/02/26 12:36:18 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_node(t_node *current)
{
	int		i;
	int		in_single;
	int		in_double;
	char	*trimmed;

	i = -1;
	in_single = 0;
	in_double = 0;
	while (current->content[++i])
	{
		handle_quotes(current->content[i], &in_single, &in_double);
		if (!in_single && current->content[i] == '$' && current->content[i + 1])
			if (process_env_if_needed(current, &i, in_single))
				return (1);
	}
	// if (!(current->content = expand_tilde(current->content)))
	// 	return (1);
	if (!in_double && current->content[0] == '"' &&
		current->content[ft_strlen(current->content) - 1] == '"')
	{
		trimmed = ft_strremove(ft_strtrim(current->content, "\""), "\"");
		free(current->content);
		current->content = trimmed;
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
		if (trim_quotes(current) == 1)
		{
			if (process_node(current))
				return (1);
		}
		current = current->next;
	}
	return (0);
}

int	expander(t_data *data)
{
	ft_printf("Expander:\n");
	if (detect_env(data))
		return (1);
	print_list(*(data->node));
	return (0);
}
