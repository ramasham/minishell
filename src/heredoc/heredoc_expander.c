/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:31:23 by rsham             #+#    #+#             */
/*   Updated: 2025/04/09 14:40:07 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_env_var_heredoc(char *content, int *i, t_data *data)
{
    char *var_name;
    char *env_value;
    char *result;
    char *before;
    char *after;
    size_t var_len;

    var_name = extract_env_name(content + *i);
    if (!var_name)
        return (NULL);
    var_len = ft_strlen(var_name);
    env_value = get_env_value(data, var_name);
    free(var_name);
    if (!env_value)
        return (NULL);
    before = ft_substr(content, 0, *i);
    if (!before)
    {
        free(env_value);
        return (NULL);
    }
    after = ft_strdup(content + *i + var_len + 1); 
    if (!after)
    {
        free(before);
        free(env_value);
        return (NULL);
    }
    result = ft_strjoin(before, env_value);
    free(before);
    free(env_value);
    if (!result)
    {
        free(after);
        return (NULL);
    }
    *i = ft_strlen(result) - 1;
    result = ft_strjoin(result, after);
    free(after);
    return (result);
}


char *expand_heredoc_content(char *content, t_data *data)
{
    char *result;
    char *tmp;
    int i;

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
