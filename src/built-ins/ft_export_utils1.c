/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:43:45 by rsham             #+#    #+#             */
/*   Updated: 2025/04/23 16:16:51 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_with_equal(t_data *data, char *var)
{
	char	*key;
	char	*val;
	char	*new_var;
	char	*eq_pos;

	eq_pos = ft_strchr(var, '=');
	key = ft_substr(var, 0, eq_pos - var + 1);
	if (!key)
		return ;
	val = remove_quotes(eq_pos + 1);
	if (!val)
		return (free(key));
	new_var = ft_strjoin(key, val);
	if (!new_var)
	{
		free(key);
		free(val);
		return ;
	}
	if (!update_existing_var(data, new_var, ft_strchr(new_var, '=')))
		if (!add_new_var(data, new_var))
			perror("minishell: export");
	free(key);
	free(val);
	free(new_var);
}

void	add_or_update_env(t_data *data, char *var)
{
	int		i;
	char	*eq_pos;
	size_t	name_len;

	eq_pos = ft_strchr(var, '=');
	if (eq_pos)
		handle_with_equal(data, var);
	else
	{
		name_len = ft_strlen(var);
		i = 0;
		while (data->envp[i])
		{
			if (ft_strncmp(data->envp[i], var, name_len) == 0 &&
				(data->envp[i][name_len] == '=' || data->envp[i][name_len] == '\0'))
				return ;
			i++;
		}
		if (!add_new_var(data, var))
			perror("minishell: export");
	}
}
