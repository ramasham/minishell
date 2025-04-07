/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:43:06 by rsham             #+#    #+#             */
/*   Updated: 2025/04/07 23:24:52 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_token_to_list(t_node **new_lst, char *token)
{
    t_node *new_node;

    if (token[0] != '\0')
    {
        new_node = create_node(token);
        if (!new_node)
            return;
        ft_nodeadd_back(new_lst, new_node);
    }
}

int extract_word(const char *content, int i, char *token, int inside_quotes)
{
    int j;

    j = 0;
    while (content[i] && (inside_quotes || (content[i] != '|' && content[i] != '>' && content[i] != '<')))
    {
        token[j++] = content[i++];
    }
    token[j] = '\0';
    return (i);
}

int extract_operator(const char *content, int i, char *op, int inside_quotes)
{
    op[0] = content[i];
    op[1] = '\0';

    if (!inside_quotes && (content[i] == '>' || content[i] == '<') && content[i + 1] == content[i])
    {
        op[1] = content[i + 1];
        return (i + 2);
    }
    return (i + 1);
}

void process_content(t_node **new_lst, char *content)
{
    int i;
    char token[256];
    char op[3];
    int inside_quotes;

    i = 0;
    inside_quotes = 0;
    while (content[i])
    {
        if (content[i] == '"' || content[i] == '\'')
            inside_quotes = !inside_quotes;
        i = extract_word(content, i, token, inside_quotes);
        token[255] = '\0';
        add_token_to_list(new_lst, token);
        if (!inside_quotes && (content[i] == '|' || content[i] == '>' || content[i] == '<'))
        {
            i = extract_operator(content, i, op, inside_quotes);
            op[2] = '\0';
            add_token_to_list(new_lst, op);
        }
    }
}

void trim_operators(t_data *data)
{
    t_node *current;
    t_node *new_lst;
    
    new_lst = NULL;
    current = *(data->node);
    while (current)
    {
        process_content(&new_lst, current->content);
        current = current->next;
    }
    free_list(data->node);
    *(data->node) = new_lst;
}
