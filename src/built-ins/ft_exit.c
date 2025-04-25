/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:16:04 by laburomm          #+#    #+#             */
/*   Updated: 2025/04/21 11:04:04 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

static int	parse_digits(const char **str, int *found_digit)
{
	int	result;

	result = 0;
	while (**str >= '0' && **str <= '9')
	{
		*found_digit = 1;
		result = result * 10 + (**str - '0');
		(*str)++;
	}
	return (result);
}

static int	ft_atoi_exit(const char *str, char **endptr)
{
	int	result;
	int	sign;
	int	found_digit;

	str = skip_whitespace(str);
	sign = parse_sign(&str);
	result = parse_digits(&str, &found_digit);
	if (!found_digit)
	{
		if (endptr)
			*endptr = (char *)str;
		return (0);
	}
	if (endptr)
		*endptr = (char *)str;
	return (result * sign);
}

static void	exit_with_status(t_data *data, int status)
{
	cleanup_shell(data);
	exit(status);
}

void	ft_exit(t_command *command, t_data *data)
{
	int		status;
	char	*endptr;

	if (data->cmd_count == 1)
		ft_putstr_fd("exit\n", 1);
	if (!command->exe_cmd[1])
		exit_with_status(data, 0);
	status = ft_atoi_exit(command->exe_cmd[1], &endptr);
	if (*endptr != '\0')
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		exit_with_status(data, 2);
	}
	if (command->exe_cmd[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		data->last_exit_status = 1;
		return ;
	}
	exit_with_status(data, status);
}
