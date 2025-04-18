/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:49:36 by rsham             #+#    #+#             */
/*   Updated: 2025/04/18 17:29:50 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_data *data, t_command *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (cmd->exe_cmd[1] && ft_strcmp(cmd->exe_cmd[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (cmd->exe_cmd[i])
	{
		while (ft_strcmp(cmd->exe_cmd[i], "-n") == 0)
			i++;
		write(STDOUT_FILENO, cmd->exe_cmd[i], ft_strlen(cmd->exe_cmd[i]));
		if (cmd->exe_cmd[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	data->last_exit_status = 0;
}
