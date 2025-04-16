/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checking_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:23:28 by rsham             #+#    #+#             */
/*   Updated: 2025/03/01 16:32:19 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	has_invalid_redirection(char *ptr)
{
	char	*operators;
	int		i;
	int		j;

	i = 0;
	operators = "<>|";
	while (ptr[i])
	{
		if (ft_strchr(operators, ptr[i]))
		{
			j = i + 1;
			while (ptr[j] && is_space(ptr[j]))
				j++;
			if (ptr[j] && ft_strchr(operators, ptr[j]))
			{
				if (!((ptr[i] == '>' && ptr[i + 1] == '>') || (ptr[i] == '<'
							&& ptr[i + 1] == '<')))
					return (1);
			}
			i = j;
		}
		else
			i++;
	}
	return (0);
}

int	check_redirection(t_data *data)
{
	if (has_invalid_redirection(data->input))
	{
		ft_putstr_fd("Syntax error: Invalid redirection\n", 2);
		return (1);
	}
	return (0);
}

int	check_append_heredoc(t_data *data)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = data->input;
	while (ptr[i])
	{
		if (ptr[i] == '>' && ptr[i + 2] == '>')
		{
			ft_putstr_fd("invalid operator\n", 2);
			return (1);
		}
		else if (ptr[i] == '<' && ptr[i + 2] == '<')
		{
			ft_putstr_fd("invalid operator\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}
