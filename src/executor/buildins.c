/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <rsham@student.42amman.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:27:57 by laburomm          #+#    #+#             */
/*   Updated: 2025/03/08 04:42:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	built_ins(t_command *command, t_data *data)
{
	if (!command || !command->full_cmd || !command->full_cmd[0])
		return (0);
	
	// Set up redirections before executing the built-in
	set_redi(command);
	
	if (ft_strcmp(command->full_cmd[0], "echo") == 0)
	{
		ft_echo(command);
		data->last_exit_status = 0;
	}
	else if (ft_strcmp(command->full_cmd[0], "cd") == 0)
	{
		ft_cd(command->full_cmd[1], data);
	}
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
	
	// Restore standard file descriptors if needed
	if (command->infile != STDIN_FILENO)
		close(command->infile);
	if (command->outfile != STDOUT_FILENO)
		close(command->outfile);
	
	return (1);
}


