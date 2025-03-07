/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:27:57 by laburomm          #+#    #+#             */
/*   Updated: 2025/03/08 01:59:00 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	built_ins(t_command *command, t_data *data)
{
	if (!command || !command->full_cmd || !command->full_cmd[0])
		return (0);
	if (ft_strcmp(command->full_cmd[0], "echo -n") == 0)
	{
		ft_echo(command);
		data->last_exit_status = 0;
	}
	// else if (ft_strcmp(command->full_cmd[0], "cd") == 0)
	// 	ft_cd(command->full_cmd[1], data);
	else if (ft_strcmp(command->full_cmd[0], "pwd") == 0)
	{
		ft_pwd();
		data->last_exit_status = 0;
	}
	else if (ft_strcmp(command->full_cmd[0], "export") == 0)
	{
		ft_export(data, command);
		data->last_exit_status = 0;
	}
	else if (ft_strcmp(command->full_cmd[0], "unset") == 0)
	{
		ft_unset(data, command);
		data->last_exit_status = 0;
	}
	else if (ft_strcmp(command->full_cmd[0], "env") == 0)
	{
		ft_env(data->envp);
		data->last_exit_status = 0;
	}
	else if (ft_strcmp(command->full_cmd[0], "exit") == 0)
		ft_exit(command, data);
	else
		return (0);
	return (1);
}


