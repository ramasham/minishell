/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:53:42 by rsham             #+#    #+#             */
/*   Updated: 2025/03/05 20:30:14 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_2d(char **str)
{
    int     i;
    
    i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

void	free_full_cmd(t_command *cmd)
{
	int	i;

	if (cmd)
	{
		if (cmd->full_cmd)
		{
			i = 0;
			while (cmd->full_cmd[i])
			{
				free(cmd->full_cmd[i]);
				i++;
			}
			free(cmd->full_cmd);
		}
		free(cmd);
	}
}

void	free_list_cmd(t_command **cmds)
{
	t_command	*tmp;

	if (!cmds || !*cmds)
		return ;
	while (*cmds)
	{
		tmp = *cmds;
		*cmds = (*cmds)->next;
		free_full_cmd(tmp);
	}
	*cmds = NULL;
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
		free(tmp->content);
		free(tmp);
	}
	*node = NULL;
}
