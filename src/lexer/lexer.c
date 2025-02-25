/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:26:31 by rsham             #+#    #+#             */
/*   Updated: 2025/02/25 14:30:42 by laburomm         ###   ########.fr       */
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
int    validate_input(t_data *data)
{
    if (operator_at_start(data))
        return (1);   
    if (check_unclosed_quotes(data))
        return (1);
    if (check_multiple_pipes(data))
        return (1);
    if (check_redirection(data))
        return (1);
    if (operator_at_end(data))
        return (1);
    if (check_append_heredoc(data))
        return (1);
    return (0);
}

int  tokenizer(t_data *data)
{
    if (validate_input(data))
        return (1);
    split_input(data);
    trim_operators(data);
    print_list(*(data->node));
    return (0);
    free_list((data->node));
    // data->node = NULL; 
}
