/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:23:28 by rsham             #+#    #+#             */
/*   Updated: 2025/02/17 12:43:47 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


int has_invalid_redirection(char *ptr)
{
    char    *operators;
    int     i;
    int     j;

    i = 0; 
    operators = "<>|";
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
                    return (1);
            }
            i = j;
        }
        else
            i++;
    }
    return (0);
}

void check_redirection(t_data *data)
{
    if (has_invalid_redirection(data->input))
    {
        ft_putstr_fd("Syntax error: Invalid redirection\n", 2);
        exit(1);
    }
}

void    check_append_heredoc(t_data *data)
{
    char    *ptr;
    int     i;

    i = 0;
    ptr = data->input;
    while (ptr[i])
    {
        if (ptr[i] == '>' && ptr[i + 2] == '>')
        {
            ft_putstr_fd("invalid operator\n", 2);
            exit(1);
        }
        else if (ptr[i] == '<' && ptr[i + 2] == '<')
        {
            ft_putstr_fd("invalid operator\n", 2);
            exit(1);
        }
        i++;
    }
}

void    operator_at_end(t_data *data)
{
    char    *ptr;
    char    *operators;
    int     i;
    int     j;
    
    i = 0;
    j = 0;
    operators = "|<>";
    ptr = data->input;
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

void    operator_at_start(t_data *data)
{
    char    *ptr;
    char    *operators;
    int     i;
    
    i = 0;
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

void    validate_input(t_data *data)
{
    check_unclosed_quotes(data);
    check_multiple_pipes(data);
    check_redirection(data);
    operator_at_start(data);
    operator_at_end(data);
    check_append_heredoc(data);
}
