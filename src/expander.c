/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:33:44 by laburomm          #+#    #+#             */
/*   Updated: 2025/02/18 15:13:04 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to search for the env variable
//if env var found
//if yes -> replace the content
//if no -> error

static void    remove_last_char(char *str)
{
    if (str && *str)
        str[ft_strlen(str) - 1] = '\0';
}
char   *get_env(t_node *env_node, int i)
{
    char    *env_value;
    char    *env_cpy;
    
    if(!env_node && !env_node->content && !(*env_node->content))
        return (NULL);
    if (((env_node->content[i] >= 'a' && env_node->content[i] <= 'z')
        || (env_node->content[i] >= 'A' && env_node->content[i] <= 'Z')))
    {
        env_node->content += i;
        if (i == 2)
            remove_last_char(env_node->content);
        env_value = getenv(env_node->content);
        if (!env_value)
            env_value = "";
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

int detect_env(t_data *data)
{
    t_node  *current;
    int     i;

    current = (*data->node);
    while (current)
    {
        if (!current->content)
            return (1);
        i = 0;
        if (current->content[i] == '"')
            i++;
        if (current->content[i] == '$')
        {
            if (get_env(current, i + 1) == NULL)
                return (1);
        }
        current = current->next;
    }
    return (0);
}

void    expander(t_data *data)
{
    ft_printf("Expander:\n");
    
    detect_env(data);
    print_list(*(data->node));
}