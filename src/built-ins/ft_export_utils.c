/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:37:58 by rsham             #+#    #+#             */
/*   Updated: 2025/04/12 12:11:38 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(const char *str)
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

void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

char	**sort_env(char **envp)
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

void	print_env_sorted(char **envp)
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
		free(sorted[i]);
		i++;
	}
	free(sorted);
}

int	update_existing_var(t_data *data, char *var, char *eq_pos)
{
	int		i;
	size_t	name_len;
	char	*new_var;

	name_len = eq_pos - var;
	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], var, name_len) == 0
			&& (data->envp[i][name_len] == '=' || data->envp[i][name_len] == '\0'))
		{
			new_var = ft_strdup(var);
			if (!new_var)
				return (0);
			free(data->envp[i]);
			data->envp[i] = new_var;
			return (1);
		}
		i++;
	}
	return (0);
}
