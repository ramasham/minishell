/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:08:33 by rsham             #+#    #+#             */
/*   Updated: 2025/02/18 11:49:11 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
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
    int         exit_status;
} t_data;

void        tokenizer(t_data *data);
void        ft_nodeadd_back(t_node **head, t_node *new_node);
void        print_list(t_node *head);
void        init_data(t_data *data);
void        split_input(t_data *data);
void        trim_operators(t_data *data);
t_node      *create_node(const char *token);
TokenType   get_token_type(const char *token);
void	free_list(t_node **node);
void    check_multiple_pipes(t_data *data);
void    check_unclosed_quotes(t_data *data);
void    check_redirection(t_data *data);
void    operator_at_end(t_data *data);
void    operator_at_start(t_data *data);
void    check_append_heredoc(t_data *data);
int     is_space(char c);
void    validate_input(t_data *data);
int     has_invalid_redirection(char *ptr);
void    expander(t_data *data);
int    detect_env(t_data *data);
char   *get_env(t_data *env_node);


#endif