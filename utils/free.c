/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:53:42 by rsham             #+#    #+#             */
/*   Updated: 2025/04/16 14:30:48 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d(char **str)
{
	int	i;

	if (!str)
		return;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_list(t_node **node)
{
	t_node	*tmp;

	if (!node || !*node)
		return ;
	while (*node)
	{
		tmp = *node;
		*node = (*node)->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
	}
	*node = NULL;
}
