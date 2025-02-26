/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:12:07 by laburomm          #+#    #+#             */
/*   Updated: 2025/02/26 10:05:36 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *extract_env_name(char *s)
{
    int i;
    char *var_name;

    if(!s || s[0] != '$')
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
        while (s[i] && (ft_isalpha(s[i]) || s[i] == '_'
            || (i > 1 && ft_isdigit(s[i]))))
            i++;
        var_name = ft_substr(s, 1 , i - 1);
    }
    return(var_name);
}


char *get_env_value(char *var_name)
{
    if (ft_strcmp(var_name, "0") == 0)
        return ("minishell");
    if (ft_strcmp(var_name, "!") == 0)
        return (""); 
    if (ft_isdigit(var_name[0]))
        return ("");
    return (getenv(var_name));
}


char *replace_env_var(char *content, int i)
{
    char *var_name;
    char *env_value;
    char *new_str;
    char *before;
    char *after;
    
    var_name = extract_env_name(content + i);
    after = ft_strdup(content + i + ft_strlen(var_name) + 1);
    if (!var_name)
        return (NULL);
    env_value= get_env_value(var_name);
    free(var_name);
    if (!env_value)
        env_value = "";
    before = ft_substr(content, 0, i);
    new_str = ft_strjoin(before, env_value);
    free(before);
    before = ft_strjoin(new_str, after);
    free(new_str);
    free(after);
    if (before[0] == '"' || before[ft_strlen(before) - 1] == '"')
        before = ft_strremove(ft_strtrim(before, "\""), "\"");
    return(before);
}
int process_env_var(t_node *current, int *i, int in_single)
{
    char *new_content;
    int env_len;

    if(in_single)
        return(0);
    env_len = 0;
    new_content = replace_env_var(current->content, *i);
    if(!new_content)
        return(1);
    free(current->content);
    current->content = new_content;
    *i += env_len - 1;
    return (0); 
}

int process_env_if_needed(t_node *current, int *i, int in_single)
{
    if (current->content[*i] == '$' && !in_single)
    {
        // Handle $! as a special case
        if (current->content[*i + 1] == '!')
        {
            if (process_env_var(current, i, in_single))
                return (1);
        }
        else if (ft_isalnum(current->content[*i + 1])
            || current->content[*i + 1] == '_')
        {
            if (process_env_var(current, i, in_single))
                return (1);
        }
    }
    return (0);
}