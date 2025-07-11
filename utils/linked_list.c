/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:57:31 by rsham             #+#    #+#             */
/*   Updated: 2025/03/15 20:57:52 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_nodeadd_back(t_node **head, t_node *new_node)
{
	t_node	*temp;

	if (!head || !new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

t_node	*create_node(const char *token)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
	{
		perror("");
		return (NULL);
	}
	new_node->content = ft_strdup(token);
	if (!new_node->content)
	{
		free(new_node);
		return (NULL);
	}
	if (ft_strncmp(new_node->content, "\"", 1) == 0)
		new_node->type = DQUOTES;
	else if (ft_strncmp(new_node->content, "'", 1) == 0)
		new_node->type = SQUOTES;
	new_node->next = NULL;
	return (new_node);
}
