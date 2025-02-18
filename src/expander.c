/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:33:44 by laburomm          #+#    #+#             */
/*   Updated: 2025/02/18 15:02:53 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to search for the env variable
//if env var found
//if yes -> replace the content
//if no -> error

char   *get_env(t_node *env_node, int i)
{
    char    *env_value;
    char    *env_cpy;

    if(!env_node && !env_node->content&& !(*env_node->content))
    {
        return (NULL);
    }
    if ((env_node->content[0] == '$') && ((env_node->content[1] >= 'a'
        && env_node->content[1] <= 'z')
        || (env_node->content[1] >= 'A' && env_node->content[1] <= 'Z')))
    {
        env_value = getenv((env_node->content) + 1);
        if (env_value)
        {
            env_cpy = ft_strdup(env_value);
            if (!env_cpy)
                return (NULL);
            (env_node->content) = env_cpy;
            return (env_value);
        }
    }
    return (NULL);
}

int    detect_env(t_data *data)
{
    t_node  *current;
    
    current = (*data->node);

    while(current)
    {
        if(!current->content)
        {
            return (1);
        }
        if (current->content[0] == '$')
            get_env(current, 1);
        if (current->content[0] == '"')
            get_env(current, 2);
            
        current = current->next;
    }
    return (0);
}

// expander_split(t_data *data)
// {
//     t_node *current_node;

//     current_node = (*data->input);
    
// }
void    expander(t_data *data)
{
    ft_printf("Expander:\n");
    expander_split(data);
    detect_env(data);
    print_list(*(data->node));
}