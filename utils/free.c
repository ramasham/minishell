/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:53:42 by rsham             #+#    #+#             */
/*   Updated: 2025/03/10 21:18:14 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//free a 2D array of strings
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

//free a single command structure and its full_cmd array
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
		if (cmd->full_path)
			free(cmd->full_path);
		free(cmd);
	}
}

//free a list of commands
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

//free a list of nodes
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

// Free environment variables (assuming it's a NULL-terminated array)
// void free_envp(char ***envp)
// {
//     if (!envp || !*envp)
//         return;
//     free_2d(*envp);
//     *envp = NULL;
// }

// Clean up all allocated memory in the data structure
void cleanup_shell(t_data *data)
{
    if (!data)
        return;
    if (data->input)
        free(data->input);
    if (data->node)
    {
        free_list(data->node);
        free(data->node);
    }
    if (data->commands)
    {
        free_list_cmd(data->commands);
        free(data->commands);
    }
    if (data->heredoc)
        free(data->heredoc);
    // if (data->envp)
    //     free_2d((data->envp));
    free(data);
}
