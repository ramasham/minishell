/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 23:23:13 by rsham             #+#    #+#             */
/*   Updated: 2025/03/08 23:23:13 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    init_data(t_data *data)
{
    data->input = NULL;
    data->node = NULL;
    data->commands = NULL;
    data->last_exit_status = 0;
    data->envp = NULL;
    data->cmd_count = 0;
    data->heredoc = NULL;
}

void	free_env(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
char **get_env(char **envp)
{
	int		size;
	char	**new_envp;
    int i;
    
	size = 0;
	while (envp[size])
		size++;
	new_envp = malloc(sizeof(char *) * ++size);
	i = 0;
	while (envp[i])
	{
		size = ft_strlen(envp[i]);
		new_envp[i] = malloc(sizeof(char)*size + 1);
		ft_strcpy(new_envp[i],envp[i]);
		i++;
 	}
	new_envp[i] = NULL;
	return (new_envp);
}

int	init_shell(t_data **data, char **envp)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
	{
		perror("minishell");
		return (1);
	}
	init_data(*data);
	(*data)->envp = get_env(envp);
	if (!(*data)->envp)
	{
		free(*data);
		return (1);
	}
	return (0);
}
