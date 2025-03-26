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
	if (!envp)
		return;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}



void get_env(t_data *data, char **envp)
{
    int size = 0;
    int i;

    while (envp[size])
        size++;
    data->envp = malloc(sizeof(char *) * (size + 1)); // Allocate memory for envp
    if (!data->envp)
        return;
    
    i = 0;
    while (envp[i])
    {
        size = ft_strlen(envp[i]);
        data->envp[i] = malloc(sizeof(char) * (size + 1)); // Allocate memory for each string
        if (!data->envp[i]) // Handle malloc failure
        {
            while (--i >= 0)
                free(data->envp[i]);
            free(data->envp);
            data->envp = NULL;
            return;
        }
        ft_strcpy(data->envp[i], envp[i]);
        i++;
    }
    data->envp[i] = NULL;
}


int	init_shell(t_data *data, char **envp)
{
	// *data = malloc(sizeof(t_data));
	// if (!*data)
	// {
	// 	perror("minishell");
	// 	return (1);
	// }
	init_data(data);
	get_env(data, envp);
	return (0);
}