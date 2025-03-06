/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:47:06 by rsham             #+#    #+#             */
/*   Updated: 2025/03/05 19:55:03 by rsham            ###   ########.fr       */
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
	ft_nodeadd_back(data->node, new_node);
	*i = 0;
}

void	process_char(t_data *data, char c, char *token, int *i)
{
	static int inside_quotes = 0;

	if (c == '"' || c == '\'')
		handle_quotes_lex(&inside_quotes, token, i, c);
	else if (c == ' ' && !inside_quotes)
	{
		if (*i > 0)
			add_token_to_list_split(data, token, i);
	}
	else
		token[(*i)++] = c;
}

void	split_input(t_data *data)
{
	char	*ptr;
	char	*token;
	int		i;

	i = 0;
	ptr = data->input;
	token = malloc(ft_strlen(data->input) + 1);
	if (!token)
	{
		ft_putstr_fd("Memory allocation failed for token\n", 2);
		return ;
	}
	data->node = malloc(sizeof(t_node *));
	if (!data->node)
	{
		free(token);
		ft_putstr_fd("Memory allocation failed for node\n", 2);
		return ;
	}
	*data->node = NULL;
	while (*ptr)
		process_char(data, *ptr++, token, &i);
	if (i > 0)
		add_token_to_list_split(data, token, &i);
	free(token);
}

