/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:23:33 by rsham             #+#    #+#             */
/*   Updated: 2025/04/22 17:53:18 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_envp(t_data *data, char **new_envp, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		new_envp[i] = ft_strdup(data->envp[i]);
		free(data->envp[i]);
		if (!new_envp[i])
		{
			while (--i >= 0)
				free(new_envp[i]);
			free(new_envp);
			return (0);
		}
		i++;
	}
	return (1);
}

int	add_new_var(t_data *data, char *var)
{
	int		size;
	char	**new_envp;

	size = 0;
	while (data->envp[size])
		size++;
	new_envp = malloc(sizeof(char *) * (size + 2));
	if (!new_envp)
		return (0);
	if (!copy_envp(data, new_envp, size))
		return (0);
	new_envp[size] = ft_strdup(var);
	new_envp[size + 1] = NULL;
	free(data->envp);
	data->envp = new_envp;
	return (1);
}

void	handle_export_arg(t_data *data, char *arg)
{
	char	*var;

	if (arg[0] == '\0')
	{
		ft_putstr_fd("bash: export: not valid in this context:\n", 2);
		data->last_exit_status = 1;
	}
	else if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		data->last_exit_status = 1;
	}
	else
	{
		var = ft_strdup(arg);
		if (!var)
			perror("bash: export");
		else
		{
			add_or_update_env(data, var);
			free(var);
		}
	}
}

void	ft_export(t_data *data, t_command *command)
{
	int	i;

	if (!command->exe_cmd[1])
		print_env_sorted(data->envp);
	else
	{
		i = 1;
		while (command->exe_cmd[i])
			handle_export_arg(data, command->exe_cmd[i++]);
	}
}
