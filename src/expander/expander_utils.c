/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:09:04 by laburomm          #+#    #+#             */
/*   Updated: 2025/02/23 17:18:44 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_q(char c)
{
    if (c == '\'')
        return (1);
    if (c == '"')
        return (2);
    return (0);    
}

void handle_quotes(char c, int *in_single, int *in_double)
{
    if(is_q(c) == 1 && !(*in_double))
        *in_single = !*in_single;
    else if(is_q(c) == 2 && !(*in_single))
        *in_double = !*in_double;     
}

int     trim_quotes(t_node *node)
{
    char    *trimmed;
    
    if (node->content[0] == '\'' && node->content[ft_strlen(node->content) - 1] == '\'')
    {
        trimmed = ft_strtrim(node->content, "'");
        free(node->content);
        node->content = trimmed;
        return (0);
    }
    return (1);
}

int process_env_var(t_node *current, int *i, int in_single)
{
    char *var_name;
    char *new_content;
    int env_len;

    if(in_single)
        return(0);
    env_len = 0;
    new_content = replace_env_var(current->content, *i);
    if(!new_content)
        return(1);
    var_name = extract_env_name(current->content + *i);
    if (var_name)
        env_len = ft_strlen(var_name);
    free(var_name);
    free(current->content);
    current->content = new_content;
    *i += env_len - 1;
    return (0); 
}

int process_env_if_needed(t_node *current, int *i, int in_single)
{
    if (current->content[*i] == '$' && !in_single
        && (ft_isalpha(current->content[*i + 1])
        || current->content[*i + 1] == '_'))
        {
            if(process_env_var(current, i, in_single))
                return(1);
        }
        return (0);
}

