/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:26:31 by rsham             #+#    #+#             */
/*   Updated: 2025/04/13 18:19:32 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    validate_input(t_data *data)
{
    // if (operator_at_start(data))
    //     return (1);   
    if (check_unclosed_quotes(data))
        return (1);
    if (check_multiple_pipes(data))
        return (1);
    // if (check_redirection(data))
    //     return (1);
    if (operator_at_end(data))
        return (1);
    // if (check_append_heredoc(data))
    //     return (1);
    return (0);
}

int  tokenizer(t_data *data)
{
    if (validate_input(data))
        return (1);
    split_input(data);
    trim_operators(data);
    // printf("tokens:\n");
    // print_list(*data->node);
    return (0);
}
