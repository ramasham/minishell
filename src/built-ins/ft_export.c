/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/12 12:23:54 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static void	print_export_error(char *arg)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	add_new_var(t_data *data, char *var)
{
	int		size;
	char	**new_envp;
	int		i;

	size = 0;
	while (data->envp[size])
		size++;
	new_envp = malloc(sizeof(char *) * (size + 2));
	if (!new_envp)
		return (0);
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
	new_envp[size] = ft_strdup(var);
	new_envp[size + 1] = NULL;
	free(data->envp);
	data->envp = new_envp;
	return (1);
}


static void	add_or_update_env(t_data *data, char *var)
{
	char	*eq_pos;

	eq_pos = ft_strchr(var, '=');
	if (!eq_pos || !update_existing_var(data, var, eq_pos))
	{
		if (!add_new_var(data, var))
		{
			perror("minishell: export");
		}
	}
}

static void	handle_export_arg(t_data *data, char *arg)
{
	char	*var;

	if (arg[0] == '\0')
	{
		ft_putstr_fd("bash: export: not valid in this context:\n", 2);
		data->last_exit_status = 1;
	}
	else if (!is_valid_identifier(arg))
	{
		print_export_error(arg);
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

	if (!command->full_cmd[1])
		print_env_sorted(data->envp);
	else
	{
		i = 1;
		while (command->full_cmd[i])
			handle_export_arg(data, command->full_cmd[i++]);
	}
}
