/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:47:06 by rsham             #+#    #+#             */
/*   Updated: 2025/03/12 01:11:58 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	process_char(t_data *data, char c, char *token, int *i)
{
	static int inside_quotes;
	
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
	data->node = malloc(sizeof(t_node));
	if (!data->node)
	{
		free(*token);
		ft_putstr_fd("Memory allocation failed\n", 2);
		return ;
	}
	*data->node = NULL;
}

void	process_input(t_data *data, char *ptr, char *token, int *i)
{
	while (*ptr)
		process_char(data, *ptr++, token, i);
}

void	split_input(t_data *data)
{
	char	*ptr;
	char	*token;
	int		i;

	i = 0;
	ptr = data->input;
	init_token_and_node(data, &token);
	if (!token || !data->node)
		return ;
	process_input(data, ptr, token, &i);
	if (i > 0)
		add_token_to_list_split(data, token, &i);
	if (!*data->node)
		free_list(data->node);
	free(token);
}
