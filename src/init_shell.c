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

int	init_shell(t_data **data, char **envp)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
	{
		perror("minishell");
		return (1);
	}
	init_data(*data);
	(*data)->envp = envp;
	return (0);
}