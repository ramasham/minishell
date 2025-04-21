/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:47:06 by rsham             #+#    #+#             */
/*   Updated: 2025/04/21 14:57:49 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quotes_lex(char *inside_quotes, char *token, int *i, char c)
{
	if (*inside_quotes == 0)
		*inside_quotes = c;
	else if (*inside_quotes == c)
		*inside_quotes = 0;
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

void	process_char(t_data *data, char c, char *token, int *i)
{
	static char	inside_quotes = 0;

	if (c == '"' || c == '\'')
		handle_quotes_lex(&inside_quotes, token, i, c);
	else if (c == ' ' && !inside_quotes)
	{
		if (*i > 0)
			add_token_to_list_split(data, token, i);
	}
	else if ((c == ';' || c == '&' || c == '|') && !inside_quotes)
	{
		if (*i > 0)
			add_token_to_list_split(data, token, i);
		token[(*i)++] = c;
		add_token_to_list_split(data, token, i);
	}
	else
		token[(*i)++] = c;
}


void	init_token_and_node(t_data *data, char **token)
{
	*token = malloc(ft_strlen(data->input) + 1);
	if (!*token)
	{
		ft_putstr_fd("Memory allocation failed\n", 2);
		return ;
	}
	data->node = ft_calloc(1, sizeof(t_node));
	if (!data->node)
	{
		free(*token);
		ft_putstr_fd("Memory allocation failed\n", 2);
		return ;
	}
}

void	split_input(t_data *data)
{
	char	*ptr;
	char	*token;
	int		i;

	i = 0;
	token = NULL;
	ptr = data->input;
	init_token_and_node(data, &token);
	if (!token || !data->node)
		return ;
	while (*ptr)
		process_char(data, *ptr++, token, &i);
	if (i > 0)
		add_token_to_list_split(data, token, &i);
	if (!*data->node)
	{
		free_list(data->node);
		free(data->node);
	}
	free(token);
}
