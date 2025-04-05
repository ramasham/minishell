/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:49:24 by rsham             #+#    #+#             */
/*   Updated: 2025/04/05 14:27:31 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int is_redirection_token(const char *str)
{
    return (str && (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0 || 
                  ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0));
}

void shift_left(char **full_cmd, int start, int len)
{
    if (!full_cmd || start >= len - 2)
        return;
    
    while (start < len - 2)
    {
        full_cmd[start] = full_cmd[start + 2];
        start++;
    }
    full_cmd[start] = NULL;
}

int parse_input_redirection(t_command *cmd, int *i, int len)
{
    if (*i + 1 >= len || is_redirection_token(cmd->full_cmd[*i + 1])) {
        ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
        return (-1);
    }
    cmd->infile = 1;
    (*i)++;
    while (*i < len && is_space_str(cmd->full_cmd[*i]))
        (*i)++;
    if (*i < len)
        cmd->input_file = ft_strdup(cmd->full_cmd[*i]);
    return (0);
}

int parse_output_redirection(t_command *cmd, int *i, int len)
{
    if (*i + 1 >= len || is_redirection_token(cmd->full_cmd[*i + 1])) {
        ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
        return (-1);
    }

    if (*i + 1 < len && cmd->full_cmd[*i + 1][0] == '>') {
        cmd->append = 1;
        (*i) += 2;
    } else {
        cmd->outfile = 1;
        (*i)++;
    }
    while (*i < len && is_space_str(cmd->full_cmd[*i]))
        (*i)++;
    if (*i < len)
        cmd->output_file = ft_strdup(cmd->full_cmd[*i]);
    return (0);
}

int parse_heredoc(t_command *cmd, int *i, int len)
{
    if (*i + 1 >= len || is_redirection_token(cmd->full_cmd[*i + 1])) {
        ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
        return (-1);
    }

    (*i) += 2;
    while (*i < len && is_space_str(cmd->full_cmd[*i]))
        (*i)++;
    if (*i < len)
        cmd->heredoc_delim = ft_strdup(cmd->full_cmd[*i]);
    return (0);
}

int handle_heredoc(const char *delimiter, t_data *data)
{
    (void)data; // Mark data as unused to prevent compiler warning
    int fd[2];
    char *line;
    
    if (pipe(fd) == -1) {
        perror("minishell: pipe");
        return (-1);
    }
    
    signal(SIGINT, heredoc_sig_handler);
    while (1) {
        line = readline(HEREDOC_PROMPT);
        if (g_exit_status == SIGINT) {
            free(line);
            close(fd[0]);
            close(fd[1]);
            return (-1);
        }
        if (!line) {
            ft_putstr_fd("minishell: warning: here-document delimited by EOF\n", 2);
            break;
        }
        if (ft_strcmp(line, delimiter) == 0) {
            free(line);
            break;
        }
        write(fd[1], line, ft_strlen(line));
        write(fd[1], "\n", 1);
        free(line);
    }
    close(fd[1]);
    signal(SIGINT, SIG_DFL);
    return (fd[0]);
}

int input_redirection(t_command *cmd, t_data *data)
{
    int fd_in;

    if (cmd->heredoc_delim) {
        fd_in = handle_heredoc(cmd->heredoc_delim, data);
        if (fd_in == -1)
            return (-1);
    }
    else if (cmd->input_file) {
        fd_in = open(cmd->input_file, O_RDONLY);
        if (fd_in == -1) {
            perror("minishell");
            return (-1);
        }
    }
    else
        return (0);
    if (dup2(fd_in, STDIN_FILENO) == -1) {
        perror("minishell");
        close(fd_in);
        return (-1);
    }
    close(fd_in);
    return (0);
}

int output_redirection(t_command *cmd)
{
    int fd_out;
    
    if (cmd->output_file) {
        if (cmd->append)
            fd_out = open(cmd->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd_out = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out == -1) {
            perror("minishell");
            return (-1);
        }
        if (dup2(fd_out, STDOUT_FILENO) == -1) {
            perror("minishell");
            close(fd_out);
            return (-1);
        }
        close(fd_out);
    }
    return (0);
}

int count_tokens(char **full_cmd)
{
    int count = 0;

    while (full_cmd && full_cmd[count])
        count++;
    return (count);
}

int parse_redirection(t_command *cmd, t_data *data)
{
    (void)data;
    int i = 0;
    int len = count_tokens(cmd->full_cmd);
    int ret;
    
    while (i < len)
    {
        if (cmd->full_cmd[i][0] == '<' && i + 1 < len && cmd->full_cmd[i][1] == '<')
        {
            if ((ret = parse_heredoc(cmd, &i, len)) != 0)
                return (ret);
            shift_left(cmd->full_cmd, i - 2, len);
            len -= 2;
        }
        else if (cmd->full_cmd[i][0] == '<')
        {
            if ((ret = parse_input_redirection(cmd, &i, len)) != 0)
                return (ret);
            shift_left(cmd->full_cmd, i - 1, len);
            len -= 2;
        }
        else if (cmd->full_cmd[i][0] == '>')
        {
            if ((ret = parse_output_redirection(cmd, &i, len)) != 0)
                return (ret);
            shift_left(cmd->full_cmd, i - 1, len);
            len -= 2;
        }
        else
            i++;
    }
    return (0);
}