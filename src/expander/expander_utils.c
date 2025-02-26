/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:09:04 by laburomm          #+#    #+#             */
/*   Updated: 2025/02/26 16:57:30 by laburomm         ###   ########.fr       */
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
// //expand_tilde
// int     expand_tilde(t_node *node)
// {
    
//     if (node->content[0] = "$")
//     {
//         char *name;
//         if (node->content[1] = "~")
//         {
//             name = getenv("HOME");
//             return (0);
//         }
//         else
//         {
//             name = NULL;
//         }
//         return (1);
//     }
// }
