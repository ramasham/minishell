/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/08 05:01:08 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h> 
# include <signal.h>

# include "libft.h"
# include "ft_printf.h"

//macros
# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126

extern int g_exit_status;

//enum
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

//struct for node linked list
typedef struct s_node
{
    char            *content;
    TokenType       type;
    struct s_node  *next;
} t_node;

//struct for commands linked list
typedef struct s_command
{
    char                **full_cmd;
    char                *full_path;
    int                 infile;
    int                 outfile;
    int                 heredoc_fd;
    struct s_command    *next;
} t_command;

//struct for data
typedef struct s_data
{
    char        *input; 
    t_node      **node;
    t_command   **commands;
    int         last_exit_status;
    int         cmd_count;
    char        **envp;
    char        *heredoc;
} t_data;


//lexer
int     extract_word(const char *content, int i, char *token);
int     extract_operator(const char *content, int i, char *op);
int     check_unclosed_quotes(t_data *data);
int     has_invalid_redirection(char *ptr);
int     check_redirection(t_data *data);
int     check_append_heredoc(t_data *data);
int     operator_at_end(t_data *data);
int     operator_at_start(t_data *data);
int     check_multiple_pipes(t_data *data);
int     validate_input(t_data *data);
int     tokenizer(t_data *data);
void	handle_quotes_lex(int *inside_quotes, char *token, int *i, char c);
void    add_token_to_list(t_node **new_lst, char *token);
void	process_char(t_data *data, char c, char *token, int *i);
void    process_content(t_node **new_lst, char *content);
void	add_token_to_list_split(t_data *data, char *token, int *i);
void    trim_operators(t_data *data);
void    split_input(t_data *data);

//expander
int     is_q(char c);
int     trim_quotes(t_node *node);
int     process_env_var(t_node *current, int *i, int in_single, t_data *data);
int     process_env_if_needed(t_node *current, int *i, int in_single , t_data *data);
int     expander(t_data *data);
int	    detect_env(t_data *data);
int     process_node(t_node *current, t_data *data);
int     handle_output_redirection(char *operator, char *filename);
int     handle_input_redirection(char  *filename);
char    *extract_env_name(char *s);
char    *get_env_value(t_data *data, char *var_name);
char    *replace_env_var(t_data *data, char *content, int i);
void    handle_quotes(char c, int *in_single, int *in_double);
void    handle_redirections(t_command *cmd);
void    set_redi(t_command *cmd);

//parser
int         get_cmd_path(t_command *cmd, t_data *data);
int         check_access(t_command *cmd, char  *path);
int         handle_heredoc(char *delimiter);
char        *join_path_cmd(char  *path, char *cmd);
char        **find_path(t_data *data);
void        add_command(t_data *data, t_command *new_cmd);
void        set_commands(t_data *data);
void        get_command(t_data *node_lst, t_node *current);
t_command   *create_new_command();

//built-ins
int     built_ins(t_command *command, t_data *data);
// int     ft_cd(t_data *data, char **args);
void ft_cd(t_data *data, char *path);

// void    ft_cd(char *path);

void    ft_exit(t_command *command, t_data *data);
void    ft_export(t_data *data, t_command *command);
void    ft_pwd(void);
void    ft_env(char **env);
void    ft_echo(t_command *command);
void    ft_unset(t_data *data, t_command *command);
// int     update_env_var(char ***envp, const char *name, const char *value);

//exectuter
int     is_external(t_command *cmd, t_data *data);
int     count_commands(t_command *cmds);
int     validate_cmd(t_data *data, t_command *cmds);
void    executor(t_data *data);
void    piping(t_data *data, int **pipe_fd);
void    child_process(t_data *data, t_command *cmd, int *pipe_fd, int index);
void    create_children(t_data *data, int *pipe_fd, pid_t *pids);
void    close_pipes(int *pipe_fd, int cmd_count);
void    execution_process(t_data *data, int **pipe_fd, pid_t *pids);
void    wait_for_children(t_data *data, pid_t *pids, int cmd_count, int *exit_status);

//signals
int     handle_eof(char *input);
void    handle_sigint(int sig);
void    setup_signal_handlers();
void    handle_sigquit(int sig);

//env
char *create_env_var(const char *name, const char *value);
// int update_env_var(char ***envp, const char *name, const char *value);

//free
void	free_full_cmd(t_command *cmd);
void	free_list_cmd(t_command **cmds);
void    free_2d(char **str);

//utils
int      is_space(char c);
char     *ft_strremove(char *str, const char *remove);
void      ft_nodeadd_back(t_node **head, t_node *new_node);
void      print_list(t_node *head);
void      init_data(t_data *data);
void	  free_list(t_node **node);
t_node    *create_node(const char *token);


#endif