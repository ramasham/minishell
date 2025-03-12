/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/12 11:18:28 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !*str || ft_isdigit(*str) || str[0] == '=')
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static char	**sort_env(char **envp)
{
	char	**sorted;
	int		size;
	int		i;
	int		j;

	size = 0;
	while (envp[size])
		size++;
	sorted = malloc(sizeof(char *) * (size + 1));
	if (!sorted)
		return (NULL);
	i = -1;
	while (++i < size)
		sorted[i] = ft_strdup(envp[i]);
	sorted[size] = NULL;
	i = -1;
	while (++i < size - 1)
	{
		j = -1;
		while (++j < size - i - 1)
			if (ft_strcmp(sorted[j], sorted[j + 1]) > 0)
				ft_swap(&sorted[j], &sorted[j + 1]);
	}
	return (sorted);
}

static void	print_env_sorted(char **envp)
{
	char	**sorted;
	char	*eq_pos;
	int		i;

	sorted = sort_env(envp);
	if (!sorted)
		return ;
	i = 0;
	while (sorted[i])
	{
		eq_pos = ft_strchr(sorted[i], '=');
		if (eq_pos)
			printf("declare -x %.*s=\"%s\"\n", (int)(eq_pos - sorted[i]), sorted[i], eq_pos + 1);
		else
			printf("declare -x %s\n", sorted[i]);
		// free(sorted[i]);
		i++;
	}
	// free(sorted);
}

static int	update_existing_var(t_data *data, char *var, char *eq_pos)
{
	int		i;
	size_t	name_len;

	name_len = eq_pos - var;
	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], var, name_len) == 0
			&& (data->envp[i][name_len] == '=' || data->envp[i][name_len] == '\0'))
		{
			// free(data->envp[i]);
			data->envp[i] = var;
			return (1);
		}
		i++;
	}
	return (0);
}

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
    int i;
    
    i = 0;
	size = 0;
	while (data->envp[size])
		size++;
	new_envp = malloc(sizeof(char *) * (size + 2));
	if (!new_envp)
		return (0);
	i = -1;
	while (++i < size)
		new_envp[i] = data->envp[i];
	new_envp[size] = var;
	new_envp[size + 1] = NULL;
	//free(data->envp);
	data->envp = new_envp;
	return (1);
}

static void	add_or_update_env(t_data *data, char *var)
{
	char	*eq_pos;

	eq_pos = ft_strchr(var, '=');
	if (!eq_pos || !update_existing_var(data, var, eq_pos))
		if (!add_new_var(data, var))
			perror("minishell: export");
}

void	ft_export(t_data *data, t_command *command)
{
	int		i;
	char	*var;

	if (!command->full_cmd[1])
	{
		print_env_sorted(data->envp);
		return ;
	}
	i = 1;
	while (command->full_cmd[i])
	{
		if (command->full_cmd[i][0] == '\0')
		{
			ft_putstr_fd("bash: export: not valid in this context:\n", 2);
			data->last_exit_status = 1;
		}
		else if (!is_valid_identifier(command->full_cmd[i]))
		{
			print_export_error(command->full_cmd[i]);
			data->last_exit_status = 1;
		}
		else
		{
			var = ft_strdup(command->full_cmd[i]);
			if (!var)
				perror("bash: export");
			else
				add_or_update_env(data, var);
		}
		i++;
	}
}
