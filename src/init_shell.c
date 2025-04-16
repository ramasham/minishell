/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:23:13 by rsham             #+#    #+#             */
/*   Updated: 2025/04/16 14:28:00 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data)
{
	data->input = NULL;
	data->pids = NULL;
	data->node = NULL;
	data->commands = NULL;
	data->last_exit_status = 0;
	data->envp = NULL;
	data->cmd_count = 0;
	data->pipe_fd = NULL;
	data->error = 0;
	data->stop = 0;
	data->empty = 0;
}

void	free_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

static int	copy_envp(t_data *data, char **envp, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		data->envp[i] = ft_strdup(envp[i]);
		if (!data->envp[i])
		{
			while (--i >= 0)
				free(data->envp[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

void	get_env(t_data *data, char **envp)
{
	int		size;

	size = 0;
	while (envp[size])
		size++;
	data->envp = malloc(sizeof(char *) * (size + 1));
	if (!data->envp)
		return ;
	if (!copy_envp(data, envp, size))
	{
		free(data->envp);
		data->envp = NULL;
		return ;
	}
	data->envp[size] = NULL;
}

int	init_shell(t_data *data, char **envp)
{
	init_data(data);
	get_env(data, envp);
	return (0);
}
