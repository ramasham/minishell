/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 01:11:30 by rsham             #+#    #+#             */
/*   Updated: 2025/03/12 01:12:02 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quotes_lex(int *inside_quotes, char *token, int *i, char c)
{
	*inside_quotes = !(*inside_quotes);
	token[(*i)++] = c;
}

void	add_token_to_list_split(t_data *data, char *token, int *i)
{
	t_node	*new_node;

	token[*i] = '\0';
	new_node = create_node(token);
	if (!new_node)
	{
		free(token);
		return ;
	}
	if (!*data->node)
		(*data->node) = new_node;
	else
		ft_nodeadd_back(data->node, new_node);
	*i = 0;
}
