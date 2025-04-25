/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:49:36 by rsham             #+#    #+#             */
/*   Updated: 2025/04/23 17:00:31 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_echo_flag(const char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] != 'n' && str[i] != 'e' && str[i] != 'E')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_data *data, t_command *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;

	while (cmd->exe_cmd[i] && is_valid_echo_flag(cmd->exe_cmd[i]))
	{
		if (ft_strchr(cmd->exe_cmd[i], 'n'))
			newline = 0;
		i++;
	}
	while (cmd->exe_cmd[i])
	{
		write(STDOUT_FILENO, cmd->exe_cmd[i], ft_strlen(cmd->exe_cmd[i]));
		if (cmd->exe_cmd[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	data->last_exit_status = 0;
}
