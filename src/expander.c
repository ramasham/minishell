/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:33:44 by laburomm          #+#    #+#             */
/*   Updated: 2025/02/19 14:39:37 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to search for the env variable
//if env var found
//if yes -> replace the content
//if no -> error


char *extract_env_name(char *s)
{
    int i;
    char *var_name;

    if(!s || s[0] != '$')
        return (NULL);
    i = 1;
    while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
        i++;
    var_name = ft_substr(s, 1 , i - 1);
    return(var_name);
    
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
    env_value= getenv(var_name);
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
        before = ft_strtrim(before, "\"");
    return(before);
}

int process_node(t_node *current)
{
    int i;
    int in_single;
    int in_double;
    char *trimmed;

    i = -1;
    in_single = 0;
    in_double = 0;
    while(current->content[++i])
    {
        handle_quotes(current->content[i] , &in_single , &in_double);
        if (!in_single && current->content[i] == '$' &&
			(ft_isalpha(current->content[i + 1]) || current->content[i + 1] == '_'))
            if (process_env_if_needed(current, &i, in_single))
                return (1);
    }
   if (in_double && current->content[0] == '"' &&
        current->content[ft_strlen(current->content) - 1] == '"')
        {
            trimmed = ft_strtrim(current->content, "\"");
            free(current->content);
            current->content = trimmed;
        }
    return (0);
}

int detect_env(t_data *data)
{
    t_node *current;

    current = (*data->node);
   
    while (current)
    {
        if (!current->content || !*(current->content))
            return (1);
        if (trim_quotes(current) == 1)
        {
            if (process_node(current))
                return (1);
        }
        current = current->next;
    }
    return (0);
}

int     expander(t_data *data)
{
    ft_printf("Expander:\n");
    if(detect_env(data))
        return(1);
    print_list(*(data->node));
    return(0);
}

