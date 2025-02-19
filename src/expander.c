/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:33:44 by laburomm          #+#    #+#             */
/*   Updated: 2025/02/19 10:16:38 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to search for the env variable
//if env var found
//if yes -> replace the content
//if no -> error

// static void    remove_last_char(char *str)
// {
//     if (str && *str)
//         str[ft_strlen(str) - 1] = '\0';
// }

// char *get_env(t_node *env_node, int i)
// {
//     char *env_value;
//     char *env_cpy;
    
//     if (!env_node || !env_node->content || !(*env_node->content))
//         return (NULL);
//     if (((env_node->content[i] >= 'a' && env_node->content[i] <= 'z')
//          || (env_node->content[i] >= 'A' && env_node->content[i] <= 'Z')))
//     {
//         char *temp = ft_strdup(env_node->content + i);
//         if (!temp)
//             return (NULL);
//         if (i == 2)
//             remove_last_char(temp);
//         env_value = getenv(temp);
//         free(temp);
//         if (!env_value)
//             env_value = "";
//         env_cpy = ft_strdup(env_value);
//         if (!env_cpy)
//             return (NULL);
//         free(env_node->content);
//         env_node->content = env_cpy;
//         return (env_cpy);
//     }
//     return (NULL);
// }

// int detect_env(t_data *data)
// {
//     t_node *current;
//     int i;

//     current = (*data->node);
//     while (current)
//     {
//         if (!current->content || !*(current->content)) // Check if content is empty
//             return (1);
//         i = 0;
//         if (current->content[i] == '"')
//             i++;
//         if (current->content[i] == '$')
//         {
//             if (get_env(current, i + 1) == NULL)
//                 return (1);
//         }
//         current = current->next;
//     }
//     return (0);
// }

// void    expander(t_data *data)
// {
//     ft_printf("Expander:\n");
//     if (!detect_env(data))
//         expander_split(data);
//     print_list(*(data->node));
// }

