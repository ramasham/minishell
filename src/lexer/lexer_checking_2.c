/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checking_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:03:25 by rsham             #+#    #+#             */
/*   Updated: 2025/03/24 01:41:04 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int    operator_at_end(t_data *data)
// {
//     char    *ptr;
//     char    *operators;
//     int     i;
//     int     j;
    
//     i = 0;
//     j = 0;
//     operators = "|<>";
//     ptr = data->input;
//     while (ptr[j])
//         j++;
//     j--;
//     while (operators[i])
//     {
//         if (ptr[j] == operators[i] && ptr[j + 1] == '\0')
//         {
//             ft_putstr_fd("invalid syntax in end \n", 2);
//             return (1);
//         }
//         i++;
//     }
//     return (0);
// }

int operator_at_end(t_data *data)
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
            ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
            ft_putchar_fd(ptr[j], 2);
            ft_putstr_fd("'\n", 2);
            return (1);
        }
        i++;
    }
    return (0);
}

// int    operator_at_start(t_data *data)
// {
//     char    *ptr;

//     ptr = data->input;
//     if (ptr[0] == '<' && ptr [1] == '<')
//     {
//         ft_printf("ptr + 3 is %s\n", ptr + 3 );
//         handle_heredoc(ptr + 3,data);
//     }
//     else
//     {
//         ft_putstr_fd("invalid syntax in start\n", 2);
//         return (1);
//     }
//     return (0);
// }
int operator_at_start(t_data *data)
{
    char    *ptr;

    ptr = data->input;
    if (ptr[0] == '|')
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
        return (1);
    }
    else if (ptr[0] == '<' && ptr[1] == '<')
    {
        // Handle heredoc
        char *delimiter = ptr + 2;
        while (*delimiter == ' ' || *delimiter == '\t')
            delimiter++;
        if (*delimiter == '\0')
        {
            ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
            return (1);
        }
        data->heredoc_delimiter = delimiter;
        return (0);
    }
    else if (ptr[0] == '<' || ptr[0] == '>')
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
        ft_putchar_fd(ptr[0], 2);
        ft_putstr_fd("'\n", 2);
        return (1);
    }
    return (0);
}

int    check_multiple_pipes(t_data *data)
{
    char    *ptr;

    ptr = data->input;
    while(*ptr)
    {
        if (*ptr == '|' && *(ptr + 1) == '|')
        {
            ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
            return (1);
        }
        ptr++;
    }
    return (0);
}
