/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:38:52 by laburomm          #+#    #+#             */
/*   Updated: 2025/04/10 13:42:47 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_only(char **export_only)
{
	int	i;

	i = 0;
	while (export_only && export_only[i])
	{
		printf("declare -x %s\n", export_only[i]);
		i++;
	}
}

int	is_in_export_only(char **export_only, char *var)
{
	int	i;

	i = 0;
	while (export_only && export_only[i])
	{
		if (ft_strcmp(export_only[i], var) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	add_to_export_only(t_data *data, char *var)
{
	int		i;
	char	**new_export;

	if (is_in_export_only(data->export_only, var))
		return ;
	i = 0;
	while (data->export_only && data->export_only[i])
		i++;
	new_export = malloc(sizeof(char *) * (i + 2));
	if (!new_export)
		return ;
	i = 0;
	while (data->export_only && data->export_only[i])
	{
		new_export[i] = data->export_only[i];
		i++;
	}
	new_export[i++] = ft_strdup(var);
	new_export[i] = NULL;
	free(data->export_only);
	data->export_only = new_export;
}

void	remove_from_export_only(t_data *data, char *var, int len)
{
	int	i;
	int	j;

	i = 0;
	while (data->export_only && data->export_only[i])
	{
		if (!ft_strncmp(data->export_only[i], var, len)
			&& data->export_only[i][len] == '\0')
		{
			free(data->export_only[i]);
			j = i;
			while (data->export_only[j])
			{
				data->export_only[j] = data->export_only[j + 1];
				j++;
			}
			break ;
		}
		i++;
	}
}
