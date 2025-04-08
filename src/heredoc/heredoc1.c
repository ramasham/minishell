/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:48:26 by laburomm          #+#    #+#             */
/*   Updated: 2025/04/09 00:35:20 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int stop(t_command *cmd, char *line)
{
    int line_len;
    int delim_len;

    if (!line || !cmd->heredoc_delim)
        return (1);
    line_len = ft_strlen(line);
    delim_len = ft_strlen(cmd->heredoc_delim);
    if (ft_strcmp(line, cmd->heredoc_delim) == 0 && (line_len == delim_len))
        return (1);
    return (0);
}

static void handle_sigint_heredoc(int sig)
{
    (void)sig;
    ft_putstr_fd("\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    exit(130);
}

static void setup_heredoc_signals(void)
{
    signal(SIGINT, handle_sigint_heredoc);
    signal(SIGQUIT, SIG_IGN);
}

int handle_heredoc(t_command *cmd, t_data *data)
{
    int     pipe_fd[2];
    char    *expanded;

    if (pipe(pipe_fd) == -1)
        return (-1);
    setup_heredoc_signals();
    while (1)
    {
        cmd->heredoc_input = readline("> ");
        if (!cmd->heredoc_input)
            break;
        if (stop(cmd, cmd->heredoc_input))
        {
            free(cmd->heredoc_input);
            break;
        }
        if (!cmd->quoted)
        {
            expanded = expand_heredoc_content(cmd->heredoc_input, data);
            if (expanded)
            {
                write(pipe_fd[1], expanded, ft_strlen(expanded));
                write(pipe_fd[1], "\n", 1);
                free(expanded);
            }
        }
        else
        {
            write(pipe_fd[1], cmd->heredoc_input, ft_strlen(cmd->heredoc_input));
            write(pipe_fd[1], "\n", 1);
        }
        free(cmd->heredoc_input);
    }
    close(pipe_fd[1]);
    return (pipe_fd[0]);
}

void parse_heredoc(t_command *cmd, int *i, int len, t_data *data)
{
    (void)len;

    if (!cmd->full_cmd[*i + 1])
    {
        ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
        return;
    }
    cmd->heredoc_delim = ft_strdup(cmd->full_cmd[*i + 1]);
    if (!cmd->heredoc_delim)
        return;
    cmd->heredoc_fd = handle_heredoc(cmd, data);
    if (cmd->heredoc_fd == -1)
    {
        free(cmd->heredoc_delim);
        cmd->heredoc_delim = NULL;
        return;
    }
    if (cmd->infile_fd != STDIN_FILENO)
        close(cmd->infile_fd);
    cmd->infile_fd = cmd->heredoc_fd;
    *i += 2;
}


int has_heredoc(t_command *cmd)
{
    int i;

    i = 0;
    while (cmd->full_cmd[i])
    {
        if (ft_strcmp(cmd->full_cmd[i], "<<") == 0)
            return (1);
        i++;
    }
    return (0);
}

void process_heredoc_with_priority(t_command *cmd, t_data *data)
{
    int i;
    int len;

    if (!cmd || !cmd->full_cmd)
        return;
    i = 0;
    len = 0;
    while (cmd->full_cmd[i])
    {
        if (ft_strcmp(cmd->full_cmd[i], "<<") == 0)
        {
            parse_heredoc(cmd, &i, len, data);
            if (!cmd->heredoc_delim)
                return;
            free(cmd->heredoc_delim);
            cmd->heredoc_delim = NULL;
        }
        else
        {
            cmd->full_cmd[len] = cmd->full_cmd[i];
            len++;
            i++;
        }
    }
    cmd->full_cmd[len] = NULL;
}
