/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:09:04 by laburomm          #+#    #+#             */
/*   Updated: 2025/04/19 10:05:39 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_q(char c)
{
	if (c == '\'')
		return (1);
	if (c == '"')
		return (2);
	return (0);
}

void	handle_quotes(char c, int *in_single, int *in_double)
{
	if (is_q(c) == 1 && !(*in_double))
		*in_single = !*in_single;
	else if (is_q(c) == 2 && !(*in_single))
		*in_double = !*in_double;
}
