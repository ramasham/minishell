/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:53:42 by rsham             #+#    #+#             */
/*   Updated: 2025/02/23 18:44:45 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_node **node)
{
	t_node	*tmp;

	if (!node || !*node)
		return ;
	while (*node)
	{
		tmp = *node;
		*node = (*node)->next;
		free(tmp->content);
		free(tmp);
	}
	*node = NULL;
}
