/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:33:44 by laburomm          #+#    #+#             */
/*   Updated: 2025/02/18 10:22:15 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to search for the env variable
//if env var found
//if yes -> replace the content
//if no -> error

char   *get_env(t_data *env_node)
{
    // t_data  *env_node;
    char    *env_value;

    // env_value = NULL;
    // env_node = NULL;
    (*env_node->node)->content++;
    if ((*env_node->node)->content == NULL)
        return (NULL);
    if (((*env_node->node)->content[0] >= 'a' && (*env_node->node)->content[0] <= 'z') 
       || ((*env_node->node)->content[0] >= 'A' && (*env_node->node)->content[0] <= 'Z'))

    {
        env_value = getenv((*env_node->node)->content);
        if (env_value)
        {
            (*env_node->node)->content = env_value;
        }
        return (env_value);
    }
    return (NULL);
}

//if no
//no env so return

int    detect_env(t_data *data)
{
    t_node  *current;

    current = *(data->node);
    while(current)
    {
        if (current->content[0] == '$')
        {
            if (get_env(data) == NULL)
                return (1); //if an error occurs
        }
        current = current->next;
    }
    return (0);
}

void    expander(t_data *data)
{
    printf("Expander:\n");
    detect_env(data);
    print_list(*(data->node));
}