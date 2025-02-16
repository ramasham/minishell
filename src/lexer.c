/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:26:31 by rsham             #+#    #+#             */
/*   Updated: 2025/02/16 18:39:17 by rsham            ###   ########.fr       */
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
int     is_space(char c)
{
    return (c == ' ' || c == '\t');
}
void    check_redirection(t_data *data)
{
    char    *operators;
    char    *ptr;
    int     i;
    int     j;

    i = 0;
    j = 0;
    operators = "<>|";
    ptr = data->input;
    while (ptr[i])
    {
        if (ft_strchr(operators, ptr[i]))
        {
            j = i + 1;
            while (ptr[j] && is_space(ptr[j]))
                j++;
            if (ptr[j] && ft_strchr(operators, ptr[j]))
            {
               if (!((ptr[i] == '>' && ptr[i + 1] == '>') || 
                      (ptr[i] == '<' && ptr[i + 1] == '<')))
                {
                    ft_putstr_fd("Syntax error: Invalid redirection\n", 2);
                    exit(1);
                }
            }
            i = j;
        }
        else
            i++;
    }
}

void    check_operators(t_data *data)
{
    char    *ptr;
    char    *operators;
    int     i;
    int     j;
    
    i = 0;
    j = 0;
    operators = "|<>";
    ptr = data->input;
    while (operators[i])
    {
        if (ptr[0] == operators[i])
        {
            ft_putstr_fd("invalid syntax in start\n", 2);
            exit(1);
        }
        i++;
    }
    i = 0;
    while (ptr[j])
        j++;
    j--;
    while (operators[i])
    {
        if (ptr[j] == operators[i] && ptr[j + 1] == '\0')
        {
            ft_putstr_fd("invalid syntax in end \n", 2);
            exit(1);
        }
        i++;
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
    char    *ptr;
    char    *token;
    int     i;
    int     inside_quotes;
    t_node  *new_node;

    i = 0;
    ptr = data->input;
    inside_quotes = 0;
    new_node = NULL;
    token = malloc(ft_strlen(data->input) + 1);
    data->node = malloc(sizeof(t_node *));
    if (!data->node)
        return;
    *data->node = NULL;
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
    t_node  *current;
    t_node  *new_node;
    t_node  **new_lst;
    char    *token;
    char    *delimiters;
    char    *copy;

    delimiters = " |><";
    current = *(data->node);
    new_node = NULL;
    new_lst = malloc(sizeof(t_node));
    if (!new_lst)
        return;
    *new_lst = NULL;
    while (current)
    {
        copy = ft_strdup(current->content);
        if (!copy)
        {
            ft_putstr_fd("allocation failed", 2);
            exit(1);
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
    check_redirection(data);
    check_operators(data);
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
