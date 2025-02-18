/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:26:31 by rsham             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/17 14:10:08 by laburomm         ###   ########.fr       */
=======
/*   Updated: 2025/02/17 19:41:07 by rsham            ###   ########.fr       */
>>>>>>> 6ab5488 (working on expander)
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
        if (current->type != DQUOTES && current->type != SQUOTES)
        {
            token = strtok(copy, delimiters);
            while (token)
            {
                new_node = create_node(token);
                ft_nodeadd_back(new_lst, new_node);
                token = strtok(NULL, delimiters);
            }
        }
        else
        {
            new_node = create_node(copy);
            ft_nodeadd_back(new_lst, new_node);
        }
         if (current->type != DQUOTES && current->type != SQUOTES)
        {
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
        }
        free(copy);
        current = current->next;
    }
    *(data->node) = *new_lst;
    free(new_lst);
}

void  tokenizer(t_data *data)
{
    printf("Tokenizer:\n");
    validate_input(data);
    split_input(data);
    trim_operators(data);
    print_list(*(data->node));
    free_list((data->node));
    data->node = NULL; 
}
