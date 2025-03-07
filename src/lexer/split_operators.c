/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <rsham@student.42amman.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:43:06 by rsham             #+#    #+#             */
/*   Updated: 2025/03/08 01:31:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_token_to_list(t_node **new_lst, char *token)
{
    t_node  *new_node;

    if (token[0] != '\0')
    {
        new_node = create_node(token);
        ft_nodeadd_back(new_lst, new_node);
    }
}

int extract_word(const char *content, int i, char *token)
{
    int j;

    j = 0;
    while (content[i] && content[i] != '|' && content[i] != '>' 
        && content[i] != '<')
    {
        token[j++] = content[i++];
    }
    token[j] = '\0';
    return (i);
}

int extract_operator(const char *content, int i, char *op)
{
    op[0] = content[i];
    op[1] = '\0';
    op[2] = '\0';

    if ((content[i] == '>' || content[i] == '<') && 
        content[i + 1] == content[i])
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

    i = 0;
    while (content[i])
    {
        i = extract_word(content, i, token);
        add_token_to_list(new_lst, token);
        if (content[i] == '|' || content[i] == '>' || content[i] == '<')
        {
            i = extract_operator(content, i, op);
            add_token_to_list(new_lst, op);
        }
    }
}

void trim_operators(t_data *data)
{
    t_node *current;
    t_node **new_lst;
    t_node *new_node;
    char *token;

    current = *(data->node);
    new_lst = malloc(sizeof(t_node *));
    if (!new_lst)
        return;
    *new_lst = NULL;
    while (current)
    {
        if (ft_strcmp(current->content, ">") == 0 ||
            ft_strcmp(current->content, "<") == 0 ||
            ft_strcmp(current->content, ">>") == 0 ||
            ft_strcmp(current->content, "<<") == 0 ||
            ft_strcmp(current->content, "|") == 0)
        {
            new_node = create_node(current->content);
            ft_nodeadd_back(new_lst, new_node);
        }
        else
        {
            token = ft_strdup(current->content);
            if (!token)
            {
                free_list(new_lst);
                return;
            }
            new_node = create_node(token);
            ft_nodeadd_back(new_lst, new_node);
            free(token);
        }
        current = current->next;
    }
    free_list(data->node);
    *(data->node) = *new_lst;
    free(new_lst);
}
