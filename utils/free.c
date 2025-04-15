/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:53:42 by rsham             #+#    #+#             */
/*   Updated: 2025/04/15 17:48:48 by rsham            ###   ########.fr       */
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

	if (!cmd)
		return;
	if (cmd->full_cmd)
	{
		i = 0;
		while (cmd->full_cmd[i])
			free(cmd->full_cmd[i++]);
		free(cmd->full_cmd);
		cmd->full_cmd = NULL;
	}
	if (cmd->full_path)
	{
		free(cmd->full_path);
		cmd->full_path = NULL;
	}
	free(cmd);
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

void	free_exec_cmd(t_command *cmd)
{
	int	i;

	if (!cmd)
		return;
	if (cmd->exe_cmd)
	{
		i = 0;
		while (cmd->exe_cmd[i])
			free(cmd->exe_cmd[i++]);
		free(cmd->exe_cmd);
		cmd->exe_cmd = NULL;
	}
	if (cmd->full_path)
	{
		free(cmd->full_path);
		cmd->full_path = NULL;
	}
	free(cmd);
}

//free a list of commands
void	free_list_exec(t_command **cmds)
{
	t_command	*tmp;

	if (!cmds || !*cmds)
		return ;
	while (*cmds)
	{
		tmp = *cmds;
		*cmds = (*cmds)->next;
		free_exec_cmd(tmp);
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
		if (tmp->content)
		free(tmp->content);
		free(tmp);
	}
	*node = NULL;
}


void cleanup_shell(t_data *data)
{
    if (!data)
        return;
    if (data->input)
        free(data->input);
    if (data->node && *data->node)
    {
        free_list(data->node);
        free(data->node);
    }
    if (data->commands)
    {
        free_list_exec(data->commands);
        free(data->commands);
    }
	if(data->envp)
		free_env(data->envp);
	if (data->pids)
		free(data->pids);
	if (data->pipe_fd)
		free(data->pipe_fd);
}
