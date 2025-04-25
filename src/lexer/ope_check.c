/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ope_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:15:05 by rsham             #+#    #+#             */
/*   Updated: 2025/04/23 10:15:37 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator_check(char c)
{
	return (c == '>' || c == '<');
}

int	skip_quotes(const char *str, int i)
{
	char	quote;

	quote = str[i];
	i++;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}

int	check_operator_error(const char *str, int *i)
{
	int	op_start;

	op_start = *i;
	while (is_operator_check(str[*i]))
		(*i)++;
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	if (is_operator_check(str[*i]))
	{
		ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
		return (1);
	}
	*i = op_start + 1;
	return (0);
}

int	check_operators(t_data *data)
{
	int			i;
	const char	*str;

	i = 0;
	str = data->input;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			i = skip_quotes(str, i);
		}
		else if (is_operator_check(str[i]))
		{
			if (check_operator_error(str, &i))
				return (1);
		}
		else
			i++;
	}
	return (0);
}
