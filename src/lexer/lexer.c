/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:26:31 by rsham             #+#    #+#             */
/*   Updated: 2025/04/15 19:14:40 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_input(t_data *data)
{
	if (check_unclosed_quotes(data))
		return (1);
	return (0);
}

int	tokenizer(t_data *data)
{
	if (validate_input(data))
		return (1);
	split_input(data);
	trim_operators(data);
	return (0);
}
