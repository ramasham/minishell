/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:36:55 by rsham             #+#    #+#             */
/*   Updated: 2025/04/12 13:04:36 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*build_result(char *before, char *env, char *after)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(before, env);
	free(before);
	free(env);
	if (!tmp)
	{
		free(after);
		return (NULL);
	}
	res = ft_strjoin(tmp, after);
	free(tmp);
	free(after);
	return (res);
}

char	*extract_env_name(char *s)
{
	int		i;
	char	*var_name;

	if (!s || s[0] != '$')
		return (NULL);
	i = 1;
	if (s[i] == '0')
		var_name = ft_strdup("0");
	else if (s[i] == '!')
		var_name = ft_strdup("!");
	else if (ft_isdigit(s[i]))
	{
		i--;
		var_name = ft_substr(s, i, i + 1);
	}
	else
	{
		while (s[i] && (ft_isalpha(s[i]) || s[i] == '_' || (i > 1
					&& ft_isdigit(s[i]))))
			i++;
		var_name = ft_substr(s, 1, i - 1);
	}
	return (var_name);
}

char	*get_env_value(t_data *data, char *var_name)
{
	int		i;
	char	*eq_pos;
	size_t	name_len;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(data->last_exit_status));
	if (ft_strcmp(var_name, "0") == 0)
		return (ft_strdup("minishell"));
	if (ft_strcmp(var_name, "!") == 0 || ft_isdigit(var_name[0]))
		return (ft_strdup(""));
	name_len = ft_strlen(var_name);
	i = 0;
	while (data->envp[i])
	{
		eq_pos = ft_strchr(data->envp[i], '=');
		if (eq_pos && (size_t)(eq_pos - data->envp[i]) == name_len
			&& !ft_strncmp(data->envp[i], var_name, name_len))
			return (ft_strdup(eq_pos + 1));
		i++;
	}
	return (ft_strdup(""));
}

char	*get_parts(char *content, int i, char **after, char **var_name)
{
	char	*name;
	size_t	len;

	name = extract_env_name(content + i);
	if (!name)
		return (NULL);
	len = ft_strlen(name);
	*after = ft_strdup(content + i + len + 1);
	*var_name = name;
	if (!*after)
	{
		free(name);
		return (NULL);
	}
	return (name);
}
