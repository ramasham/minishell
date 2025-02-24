/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/02/24 11:10:06 by laburomm         ###   ########.fr       */
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
#include <fcntl.h>

#define REDIR_OUT1 ">"
#define APPEND1 ">>"
#define REDIR_IN1 "<"
#define HERE_DOC1 "<<"
#define PIPES "|"

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

typedef struct s_command
{
    char    *full_cmd;
    char    *full_path;
    int     infile;
    int     outfile;
    struct s_command *next;
} t_command;

typedef struct s_data
{
    char        *input; 
    t_node      **node;
    t_command   **commands;
    int         exit_status;
} t_data;


// lexer_utils
void	handle_quotes_lex(int *inside_quotes, char *token, int *i, char c);
void    add_token_to_list(t_node **new_lst, char *token);
int     extract_word(const char *content, int i, char *token);
void	process_char(t_data *data, char c, char *token, int *i);
int     extract_operator(const char *content, int i, char *op);
void    process_content(t_node **new_lst, char *content);
void	add_token_to_list_split(t_data *data, char *token, int *i);

// exer_checking
int     check_unclosed_quotes(t_data *data);
int     has_invalid_redirection(char *ptr);
int     check_redirection(t_data *data);
int     check_append_heredoc(t_data *data);
int     operator_at_end(t_data *data);
int     operator_at_start(t_data *data);
int     check_multiple_pipes(t_data *data);
int     validate_input(t_data *data);

//lexer
void        trim_operators(t_data *data);
void        split_input(t_data *data);
int         tokenizer(t_data *data);
TokenType   get_token_type(const char *token);

//expander utils
int     is_q(char c);
int     process_env_if_needed(t_node *current, int *i, int in_single);
int     process_env_var(t_node *current, int *i, int in_single);
void    handle_quotes(char c, int *in_single, int *in_double);
int     trim_quotes(t_node *node);

//expander
int     expander(t_data *data);
int     detect_env(t_data *data);
char    *replace_env_var(char *content, int i);
char    *extract_env_name(char *s);
int     process_node(t_node *current);

//utils
void        ft_nodeadd_back(t_node **head, t_node *new_node);
void        print_list(t_node *head);
void        init_data(t_data *data);
void	    free_list(t_node **node);
int         is_space(char c);
t_node      *create_node(const char *token);

//redirections
void    handle_redirections(t_node *current, int *infile, int *outfile);
int     handle_output_redirection(char *operator, char *filename);
int     handle_input_redirection(char  *filename);

//parser_utils
void        print_command(t_data *newcmd);
void        add_command(t_data *data, t_command *new_cmd);
t_command   *create_new_command();


//parser
void    print_command(t_data *newcmd);
void    get_command(t_data *node_lst, t_node *current);

#endif