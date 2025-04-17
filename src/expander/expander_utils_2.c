/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:12:07 by laburomm          #+#    #+#             */
/*   Updated: 2025/04/15 19:19:37 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *trim_if_quotes(char *res)
{
	char *trimmed;
	char *new;

	if (res[0] == '"' || res[ft_strlen(res) - 1] == '"')
	{
		trimmed = ft_strtrim(res, "\"");
		if (!trimmed)
			return (free(res), NULL);
		new = ft_strremove(trimmed, "\"");
		free(trimmed);
		free(res);
		return (new);
	}
	return (res);
}



char	*replace_env_var(t_data *data, char *content, int i)
{
	char	*var;
	char	*env;
	char	*before;
	char	*after;

	var = get_parts(content, i, &after, &var);
	if (!var)
		return (NULL);
	env = get_env_value(data, var);
	free(var);
	if (!env)
		return (free(after), NULL);
	before = ft_substr(content, 0, i);
	if (!before)
		return (free(env), free(after), NULL);
	return (trim_if_quotes(build_result(before, env, after)));
}

int	process_env_var(t_node *current, int *i, int in_single, t_data *data)
{
	char	*new_content;

	if (in_single)
		return (0);
	new_content = replace_env_var(data, current->content, *i);
	if (!new_content)
		return (1);
	free(current->content);
	current->content = new_content;
	return (0);
}

int	process_env_if_needed(t_node *current, int *i, int in_single, t_data *data)
{
	if (current->content[*i] == '$' && !in_single)
	{
		if (current->content[*i + 1] == '?')
		{
			if (process_env_var(current, i, in_single, data))
				return (1);
		}
		else if (current->content[*i + 1] == '!'
			|| current->content[*i + 1] == '#')
		{
			ft_printf("minishell: invalid input: %c%c\n", current->content[*i],
				current->content[*i + 1]);
			return (1);
		}
		else if (ft_isalnum(current->content[*i + 1])
			|| current->content[*i + 1] == '_')
		{
			if (process_env_var(current, i, in_single, data))
				return (1);
		}
	}
	return (0);
}
