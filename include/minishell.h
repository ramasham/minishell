/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 01:14:51 by rsham             #+#    #+#             */
/*   Updated: 2025/04/17 19:12:55 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>

// macros
# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126
# define SPACES " \t\n\v\f\r"

extern int				g_exit_status;

// enum
typedef enum s_type
{
	NONE,
	DQUOTES,
	SQUOTES,
}						t_type;

// struct for node linked list
typedef struct s_node
{
	char				*content;
	t_type				type;
	struct s_node		*next;
}						t_node;

// struct for commands linked list
typedef struct s_command
{
	char				**full_cmd;
	char				**exe_cmd;
	char				*full_path;
	int					infile_fd;
	int					outfile_fd;
	int					append;
	int					heredoc_fd;
	char				*output_file;
	char				*input_file;
	char				*heredoc_delim;
	char				*heredoc_input;
	int					quoted;
	int					skip;
	struct s_command	*next;
}						t_command;

// struct for data
typedef struct s_data
{
	char				*input;
	t_node				**node;
	t_command			**commands;
	int					last_exit_status;
	int					cmd_count;
	char				**envp;
	int					*pipe_fd;
	pid_t				*pids;
	int					error;
	int					stop;
	int					empty;
}						t_data;

// shell
int						init_shell(t_data *data, char **envp);

// lexer
int						extract_word(const char *content, int i, char *token,
							int inside_quotes);
int						extract_operator(const char *content, int i, char *op,
							int inside_quotes);
int						check_unclosed_quotes(t_data *data);
int						validate_input(t_data *data);
int						tokenizer(t_data *data);
void					handle_quotes_lex(int *inside_quotes, char *token,
							int *i, char c);
void					add_token_to_list(t_node **new_lst, char *token);
void					process_char(t_data *data, char c, char *token, int *i);
void					process_content(t_node **new_lst, char *content);
void					add_token_to_list_split(t_data *data, char *token,
							int *i);
void					trim_operators(t_data *data);
void					split_input(t_data *data);
void					init_token_and_node(t_data *data, char **token);

// expander
int						is_q(char c);
int						trim_quotes(t_node *node);
int						process_env_var(t_node *current, int *i, int in_single,
							t_data *data);
int						process_env_if_needed(t_node *current, int *i,
							int in_single, t_data *data);
int						expander(t_data *data);
int						detect_env(t_data *data);
char					*trim_if_quotes(char *res);
char					*replace_env_var(t_data *data, char *content, int i);
int						process_env_var(t_node *current, int *i, int in_single,
							t_data *data);
int						process_env_if_needed(t_node *current, int *i,
							int in_single, t_data *data);
char					*build_result(char *before, char *env, char *after);
char					*extract_env_name(char *s);
char					*get_env_value(t_data *data, char *var_name);
char					*get_parts(char *content, int i, char **after,
							char **var_name);

int						process_node(t_node *current, t_data *data);
char					*extract_env_name(char *s);
char					*get_parts(char *content, int i, char **after,
							char **var_name);
char					*get_env_value(t_data *data, char *var_name);
char					*replace_env_var(t_data *data, char *content, int i);
void					handle_quotes(char c, int *in_single, int *in_double);

// parser
int						get_cmd_path(t_command *cmd, t_data *data);
int						check_access(t_data *data, t_command *cmd, char *path);
char					*join_path_cmd(char *path, char *cmd);
char					**find_path(t_data *data);
void					add_command(t_data *data, t_command *new_cmd);
int						set_commands(t_data *data);
void					get_command(t_data *node_lst, t_node *current);
int						is_abs_path(char *cmd);
int						handle_abs_path(t_command *cmd);
int						parse_redirection(t_command *cmd, t_data *data);
void					cleanup_redirections(t_command *cmd);
int						handle_input_redirection(t_command *cmd,
							char *filename);
int						parse_output(t_data *data, t_command *cmd, int *i);
int						handle_output_redirection(t_data *data, t_command *cmd,
							char *filename, int append);
t_command				*create_new_command(void);
t_command				*create_and_initialize_cmd(void);
int						is_operator(char *str);
int						create_exec_cmd(t_data *data, t_command *cmd);

// heredoc
int						handle_heredoc(t_command *cmd, t_data *data);
char					*expand_heredoc_content(char *content, t_data *data);
int						parse_heredoc(t_command *cmd, int *i, t_data *data);
void					heredoc_delim(t_command *cmd, int *i);
void					cleanup_heredoc(t_command *cmd);
char					*expand_env_var_heredoc(char *content, int *i,
							t_data *data);
char					*expand_heredoc_content(char *content, t_data *data);
void					setup_heredoc_signals(void);
int						stop(t_command *cmd, char *line);

// built-ins
int						built_ins(t_command *command, t_data *data);
int						is_valid_identifier(const char *str);

int						update_existing_var(t_data *data, char *var,
							char *eq_pos);
int						update_existing_var(t_data *data, char *var,
							char *eq_pos);
void					ft_cd(t_data *data, char *path);
void					ft_exit(t_command *command, t_data *data);
void					ft_export(t_data *data, t_command *command);
void					ft_swap(char **a, char **b);
char					**sort_env(char **envp);
void					print_env_sorted(char **envp);

void					ft_pwd(void);
void					ft_env(char **env);
void					ft_echo(t_data *data, t_command *command);
void					ft_unset(t_data *data, t_command *command);

// exectuter
int						count_commands(t_command *cmds);
int						executor(t_data *data);
int						execution_process(t_data *data);
int						piping(t_data *data);
void					close_pipes(t_data *data, int cmd_count);
void					wait_for_children(t_data *data, int cmd_count,
							int *exit_status);
void					child_process(t_data *data, t_command *cmd);
int						setup_children(t_data *data);
int						forking(t_data *data, t_command *cmd, int i);
int						setup_fds(t_command *cmd);
void					setup_pipes(t_data *data, int i);


// signals
int						handle_eof(char *input);
void					handle_sigint(int sig);
void					setup_signal_handlers(void);
void					handle_sigquit(int sig);

// env
int						find_env_var(t_data *data, const char *name,
							char **env_var, char **eq_pos);
int						update_envp(t_data *data, int index, char *new_var);
int						my_setenv(t_data *data, const char *name,
							const char *value, int overwrite);
char					*create_new_var(const char *name, const char *value);
void					update_env_vars(t_data *data, char *oldpwd,
							char *newpwd);

// free
void					free_full_cmd(t_command *cmd);
void					free_list_cmd(t_command **cmds);
void					free_2d(char **str);
void					cleanup_shell(t_data *data);
void					free_env(char **envp);
void					close_fds_and_cleanup(t_command *cmd);
void					handle_child_failure(t_command *cmd, t_data *data,
							int exit_code);
void					clean_exe_list(t_data *data);

// utils
int						is_space(char c);
char					*ft_strremove(char *str, const char *remove);
void					ft_nodeadd_back(t_node **head, t_node *new_node);
void					init_data(t_data *data);
void					free_list(t_node **node);
int						is_space_str(char *str);
t_node					*create_node(const char *token);
void					free_exec_cmd(t_command *cmd);
void					free_list_exec(t_command **cmds);
void					cleanup_exe(t_data *data);
void					cleanup_cmd(t_data *data);
void					handle_execve_error(t_command *cmd, t_data *data);
void					pre_exec_checks(t_command *cmd, t_data *data);
void					clean_pids_pipes(t_data *data);
void					remove_quotes_from_command(t_command *cmd);

// other
void					print_command_exec(t_data *newcmd);
void					print_list(t_node *head);
void					print_command(t_data *newcmd);
void					ft_error(const char *cmd, const char *msg);
char	*remove_quotes(const char *str, int remove_all);


#endif
