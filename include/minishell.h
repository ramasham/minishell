/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:08:33 by rsham             #+#    #+#             */
/*   Updated: 2025/02/16 18:20:51 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum
{
    ARG,
    REDIR_IN,
    REDIR_OUT,
    HERE_DOC,
    APPEND,
    PIPE,
    CMD,
    DQUOTES,
    SQUOTES,
} TokenType;

typedef struct s_node
{
    char            *content;
    TokenType       type;
    struct s_node  *next;
} t_node;

typedef struct s_data
{
    char        *input; 
    t_node      **node;
} t_data;

void        tokenizer(t_data *data);
void        ft_nodeadd_back(t_node **head, t_node *new_node);
void        print_list(t_node *head);
void        init_data(t_data *data);
void        split_input(t_data *data);
void        trim_operators(t_data *data);
t_node      *create_node(const char *token);
TokenType   get_token_type(const char *token);
// void   trim_pipe(t_data *data);
void	free_list(t_node **node);
void    check_multiple_pipes(t_data *data);
void    check_unclosed_quotes(t_data *data);
void    check_redirection(t_data *data);
void    check_operators(t_data *data);







#endif