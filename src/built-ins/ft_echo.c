/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:49:36 by rsham             #+#    #+#             */
/*   Updated: 2025/04/21 15:50:23 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_n_flag(const char *str)
{
	int	i;

	i = 0;
	if (str[i++] != '-')
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
	if (cmd->exe_cmd[1] && is_valid_n_flag(cmd->exe_cmd[i]))
	{
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
