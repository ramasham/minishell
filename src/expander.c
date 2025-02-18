/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:33:44 by laburomm          #+#    #+#             */
/*   Updated: 2025/02/18 13:55:02 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to search for the env variable
//if env var found
//if yes -> replace the content
//if no -> error

char   *get_env(t_node *env_node)
{
    char    *env_value;
    char    *env_cpy;

    ft_printf("content[0] in get env %c\n", (env_node->content[0]));
    if(!env_node && !env_node->content&& !(*env_node->content))
    {
        return (ft_printf("error 8 \n"), NULL);
    }
    if ((env_node->content[0] == '$' ) && (env_node->content[1] >= 'a' && env_node->content[1] <= 'z') 
    || (env_node->content[1] >= 'A' && env_node->content[1] <= 'Z'))
    {
        env_value = getenv((env_node->content) + 1);
        if (env_value)
        {
            env_cpy = ft_strdup(env_value);
            if (!env_cpy)
                return (ft_printf("error 3\n"),NULL);
            //free((*env_node->node)->content); 
            (env_node->content) = env_cpy;
            return (ft_printf("error 4\n"),env_value);
        }
    }
    return (NULL);
}

int    detect_env(t_data *data)
{
    ft_printf("error 6\n");
    t_node  *current;
    ft_printf("error 7\n");
    
    current = (*data->node);
    
    ft_printf("content[0] before while %s\n", current->content);
    // printf("nodelist:\n");
    // print_list(*(data->node));
    while(current)
    {
        if(!current->content)
        {
            return (ft_printf("error 9\n"), 1);
        }
        ft_printf("content[0] afetr while %s\n", current->content);
        printf("nodelist:\n");
        print_list(*(data->node));
        ft_printf("dollar %c\n", current->content[0]);
        if (current->content[0] == '$')
        {
            if (get_env(current->content) == NULL)
                return (ft_printf("error 1\n"), 1); //if an error occurs
        }
        current = current->next;
    }
    return (ft_printf("error 2\n"),0);
}


void    expander(t_data *data)
{
    ft_printf("Expander:\n");
    detect_env(data);
    print_list(*(data->node));
}