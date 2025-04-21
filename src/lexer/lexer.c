/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:26:31 by rsham             #+#    #+#             */
/*   Updated: 2025/04/21 17:34:26 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	check_operators(t_data *data)
// {
// 	const char	*ptr;
// 	int		i;
	
// 	i = 0;
// 	ptr = data->input;
// 	while (ptr[i])
// 	{
// 		if (ptr[0] == '"')
// 			return (0);
// 		if ((ptr[i] == '>' || ptr[i] == '<') && (ptr[i + 1] == ' ' || ptr[i + 1] == '\t'))
// 		{
// 			ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
// 			return (1);	
// 		}
// 		i++;
// 	}
// 	return (0);
	
// }

int	is_operator_check(char c)
{
	return (c == '>' || c == '<');
}

int	skip_quotes(const char *str, int i)
{
	char	quote = str[i];

	i++;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == quote)
		i++;
	return (i);
}

int	check_operators(t_data *data)
{
	const char	*str = data->input;
	int			i = 0;

	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			i = skip_quotes(str, i);
			continue;
		}
		if (is_operator_check(str[i]))
		{
			int	op_start = i;
			while (is_operator_check(str[i]))
				i++;
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			if (is_operator_check(str[i]))
			{
				ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
				return (1);
			}
			i = op_start + 1;
		}
		else
			i++;
	}
	return (0);
}

int	check_unclosed_quotes(t_data *data)
{
	char	*ptr;
	int		double_quotes;
	int		single_quotes;

	ptr = data->input;
	double_quotes = 0;
	single_quotes = 0;
	while (*ptr)
	{
		if (*ptr == '"' && single_quotes == 0)
		{
			double_quotes = !double_quotes;
		}
		else if (*ptr == '\'' && double_quotes == 0)
			single_quotes = !single_quotes;
		ptr++;
	}
	if (double_quotes || single_quotes)
	{
		ft_putstr_fd("Syntax error: Unclosed quotes\n", 2);
		return (1);
	}
	return (0);
}

int	tokenizer(t_data *data)
{
	if (check_unclosed_quotes(data))
		return (1);
	if (check_operators(data))
		return (1);
	split_input(data);
	trim_operators(data);
	return (0);
}
