/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:31:23 by rsham             #+#    #+#             */
/*   Updated: 2025/04/12 11:14:13 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_var(char *content, int *i, t_data *data, size_t *var_len)
{
	char	*name;
	char	*val;

	name = extract_env_name(content + *i);
	if (!name)
		return (NULL);
	*var_len = ft_strlen(name);
	val = get_env_value(data, name);
	free(name);
	return (val);
}

static char	*join_parts(char *before, char *env, char *after)
{
	char	*res;
	char	*temp;

	temp = ft_strjoin(before, env);
	free(before);
	free(env);
	if (!temp)
	{
		free(after);
		return (NULL);
	}
	res = ft_strjoin(temp, after);
	free(temp);
	free(after);
	return (res);
}

char	*expand_env_var_heredoc(char *content, int *i, t_data *data)
{
	char	*env;
	char	*before;
	char	*after;
	size_t	var_len;

	env = get_env_var(content, i, data, &var_len);
	if (!env)
		return (NULL);
	before = ft_substr(content, 0, *i);
	if (!before)
		return (free(env), NULL);
	after = ft_strdup(content + *i + var_len + 1);
	if (!after)
		return (free(before), free(env), NULL);
	*i = ft_strlen(before) + ft_strlen(env) - 1;
	return (join_parts(before, env, after));
}

char	*expand_heredoc_content(char *content, t_data *data)
{
	char	*result;
	char	*tmp;
	int		i;

	if (!content)
		return (NULL);
	result = ft_strdup(content);
	if (!result)
		return (NULL);
	i = -1;
	while (result[++i])
	{
		if (result[i] == '$' && result[i + 1])
		{
			tmp = expand_env_var_heredoc(result, &i, data);
			if (!tmp)
			{
				free(result);
				return (NULL);
			}
			free(result);
			result = tmp;
		}
	}
	return (result);
}
