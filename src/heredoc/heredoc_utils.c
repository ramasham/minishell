/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:48:20 by laburomm          #+#    #+#             */
/*   Updated: 2025/04/06 01:06:34 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *expand_env_var_heredoc(char *content, int *i, t_data *data)
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

    var_len = ft_strlen(var_name); // ✅ Store length before freeing
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

    after = ft_strdup(content + *i + var_len + 1); // ✅ Use var_len
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
    i = 0;
    while (result[i])
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
        i++;
    }
    return (result);
}

void cleanup_heredoc(t_command *cmd)
{
    if (cmd->heredoc_fd != -1)
        close(cmd->heredoc_fd);
    if (cmd->heredoc_delim)
        free(cmd->heredoc_delim);
    cmd->heredoc_fd = -1;
    cmd->heredoc_delim = NULL;
}

