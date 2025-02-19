/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checking_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:03:25 by rsham             #+#    #+#             */
/*   Updated: 2025/02/19 17:05:26 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    operator_at_end(t_data *data)
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
            return (1);
        }
        i++;
    }
    return (0);
}

int    operator_at_start(t_data *data)
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
            return (1);
        }
        i++;
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
