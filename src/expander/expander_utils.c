/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 12:09:04 by laburomm          #+#    #+#             */
/*   Updated: 2025/02/24 14:20:04 by laburomm         ###   ########.fr       */
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
