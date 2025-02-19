/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:08:33 by rsham             #+#    #+#             */
/*   Updated: 2025/02/19 14:42:45 by laburomm         ###   ########.fr       */
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

int        tokenizer(t_data *data);
void        ft_nodeadd_back(t_node **head, t_node *new_node);
void        print_list(t_node *head);
void        init_data(t_data *data);
void        split_input(t_data *data);
void        trim_operators(t_data *data);
t_node      *create_node(const char *token);
TokenType   get_token_type(const char *token);
void	free_list(t_node **node);
int    check_multiple_pipes(t_data *data);
int    check_unclosed_quotes(t_data *data);
int    check_redirection(t_data *data);
int    operator_at_end(t_data *data);
int     operator_at_start(t_data *data);
int    check_append_heredoc(t_data *data);
int     is_space(char c);
int     validate_input(t_data *data);
int     has_invalid_redirection(char *ptr);
//expander
int    expander(t_data *data);
int    detect_env(t_data *data);
char *replace_env_var(char *content, int i);
char *extract_env_name(char *s);
int process_node(t_node *current);
//expander utils
int process_env_if_needed(t_node *current, int *i, int in_single);
int process_env_var(t_node *current, int *i, int in_single);
void handle_quotes(char c, int *in_single, int *in_double);
int is_q(char c);
int     trim_quotes(t_node *node);

#endif