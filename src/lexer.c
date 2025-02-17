/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:26:31 by rsham             #+#    #+#             */
/*   Updated: 2025/02/16 13:28:11 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

TokenType get_token_type(const char *token)
{
    if (ft_strcmp(token, "|") == 0)
        return (PIPE);
    else if (ft_strcmp(token, "<") == 0)
        return (REDIR_IN);
    else if (ft_strcmp(token, ">") == 0)
        return (REDIR_OUT);
    else if (ft_strcmp(token, ">>") == 0)
        return (APPEND);
    else if (ft_strcmp(token, "<<") == 0)
        return (HERE_DOC);
    return (ARG);
}
void    check_unclosed_quotes(t_data *data)
{
    char    *ptr;
    int     double_quotes;
    int     single_quotes;

    ptr = data->input;
    double_quotes = 0;
    single_quotes = 0;
    while (*ptr)
    {
        if (*ptr == '"')
            double_quotes++;            
        if (*ptr == '\'')
            single_quotes++;
        ptr++;
    }
    if (double_quotes % 2 != 0 || single_quotes % 2 != 0)
    {
        ft_putstr_fd("Syntax error: Unclosed quotes\n", 2);
        exit(1);
    }
}

void    check_multiple_pipes(t_data *data)
{
    char    *ptr;

    ptr = data->input;
    while(*ptr)
    {
        if (*ptr == '|' && *(ptr + 1) == '|')
        {
            ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
            exit(1);
        }
        ptr++;
    }
}
void    split_input(t_data *data) 
{
    char *ptr;
    char *token;
    int i;
    int inside_quotes;
    t_node  *new_node;

    i = 0;
    ptr = data->input;
    token = malloc(ft_strlen(data->input) + 1);
    if (!data->node)
    {
        data->node = malloc(sizeof(t_node));
        *(data->node) = NULL;
    }
    inside_quotes = 0;
    while (*ptr) 
    {
        if (*ptr == '"' || *ptr == '\'')
        {
            inside_quotes = !inside_quotes;
            token[i++] = *ptr;
        }
        else if (*ptr == ' ' && !inside_quotes) 
        {
            if (i > 0) 
            {
                token[i] = '\0';
                new_node = create_node(token);
                ft_nodeadd_back(data->node, new_node);
                i = 0;
            }
        }
        else
            token[i++] = *ptr;
        ptr++;
    }
    if (i > 0)
    {
        token[i] = '\0';
        new_node = create_node(token);
        ft_nodeadd_back(data->node, new_node);
    }
}

void trim_operators(t_data *data)
{
    t_node  *current = *(data->node);
    t_node  *new_node = NULL;
    t_node  **new_lst;
    char    *token;
    char    *delimiters = " |><";
    char    *copy;

    new_lst = malloc(sizeof(t_node));
    if (!new_lst)
        return;
    *new_lst = NULL;
    while (current)
    {
        copy = ft_strdup(current->content);
        if (!copy)
        {
            current = current->next;
            continue;
        }
        token = strtok(copy, delimiters);
        while (token)
        {
            new_node = create_node(token);
            ft_nodeadd_back(new_lst, new_node);
            token = strtok(NULL, delimiters);
        }
        if (ft_strchr(current->content, '|'))
            ft_nodeadd_back(new_lst, create_node("|"));
        else if (ft_strncmp(current->content, ">>", 2) == 0)
            ft_nodeadd_back(new_lst, create_node(">>"));
        else if (ft_strncmp(current->content, "<<", 2) == 0)
            ft_nodeadd_back(new_lst, create_node("<<"));
        else if (ft_strchr(current->content, '>'))
            ft_nodeadd_back(new_lst, create_node(">"));
        else if (ft_strchr(current->content, '<'))
            ft_nodeadd_back(new_lst, create_node("<"));
        free(copy);
        current = current->next;
    }
    *(data->node) = *new_lst;
    free(new_lst);
}

void    validate_input(t_data *data)
{
    check_unclosed_quotes(data);
    check_multiple_pipes(data);
}

void  tokenizer(t_data *data)
{
    validate_input(data);
    split_input(data);
    trim_operators(data);
    print_list(*(data->node));
    free_list((data->node));
    data->node = NULL; 
}
