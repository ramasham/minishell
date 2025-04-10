/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:23:23 by rsham             #+#    #+#             */
/*   Updated: 2025/04/08 19:54:12 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cleanup_child(t_data *data)
{
    if (data->pipe_fd)
        free(data->pipe_fd);
    if (data->pids)
        free(data->pids);
    if (data->commands)
    {
        free_list_cmd(data->commands);
        free(data->commands);
    }
    free_env(data->envp);
}

void    wait_for_children(t_data  *data, int cmd_count, int *exit_status)
{
    int i;
    int status;

    i = 0;
    while (i < cmd_count)
    {
        signal(SIGINT, SIG_IGN);
        waitpid(data->pids[i], &status, 0);
        if (WIFEXITED(status))
        {
            *exit_status = WEXITSTATUS(status);
            if (*exit_status == 0)
                data->last_exit_status = 0;
        }
        else if (WIFSIGNALED(status))
            *exit_status = 128 + WTERMSIG(status);
        else
            *exit_status = 1;
        i++;
    }
}

void init_cmd(t_command *cmd)
{
    cmd->output_files = malloc(sizeof(char *) * 10);
    cmd->output_fds = malloc(sizeof(int) * 10);
    cmd->outfile_count = 0;
    cmd->last_infile_fd = -1;
    cmd->heredoc_fd = -1;
}


int handle_dup2(t_command *cmd)
{
    if (cmd->heredoc_fd != -1)
    {
        if (dup2(cmd->heredoc_fd, STDIN_FILENO) == -1)
        {
            perror("dup2 heredoc failed");
            return (-1);
        }
        close(cmd->heredoc_fd);
    }
    else if (cmd->last_infile_fd != -1)
    {
        if (dup2(cmd->last_infile_fd, STDIN_FILENO) == -1)
        {
            perror("dup2 infile failed");
            return (-1);
        }
        close(cmd->last_infile_fd);
    }

    if (cmd->outfile_count > 0)
    {
        if (output_redirection(cmd) == -1)
            return (-1);
    }
    return (0);
}


int child_process(t_data *data, t_command *cmd)
{
    init_cmd(cmd);// initialize all fds to -1
    // if (is_redirection(cmd))
    //     handle_dup2(cmd, data);
    parse_redirection(cmd);
    if (handle_dup2(cmd) == -1)
    {
        cleanup_child(data);
        exit(1);
    }
    if (ft_strcmp(cmd->full_cmd[0], "exit") == 0)
        ft_exit(cmd, data);
    get_cmd_path(cmd, data);
    if (check_path(data) != 0)
    {
        cleanup_child(data);
        exit(data->last_exit_status);
    }
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    execve(cmd->full_path, cmd->full_cmd, data->envp);
    cleanup_child(data);
    exit(data->last_exit_status);
}
void setup_redirection(t_data *data, int i)
{
    if (i > 0)
    {
        if (dup2(data->pipe_fd[(i - 1) * 2], STDIN_FILENO) == -1)
        {
            perror("dup2 failed for input pipe");
            return;
        }
    }
    if (i < data->cmd_count - 1)
    {
        if (dup2(data->pipe_fd[i * 2 + 1], STDOUT_FILENO) == -1)
        {
            perror("dup2 failed for output pipe");
            return;
        }
    }
}

int     forking(t_data *data, t_command *cmd, int i)
{
    data->pids[i] = fork();
    if (data->pids[i] == -1)
    {
        perror("fork failed");
        cleanup_child(data);
        return(1);
    }
    if (data->pids[i] == 0)
    {
        setup_redirection(data, i);
        close_pipes(data, data->cmd_count);
        if (child_process(data, cmd))
        {
            cleanup_child(data);
            exit(1);
        }
    }
    return (0);
}

int  setup_children(t_data *data)
{
    int i;
    t_command *cmd;
    
    i = 0;
    cmd = (*data->commands);
    while (cmd)
    {
        if (forking(data, cmd, i))
            return (1);
        cmd = cmd->next;
        i++;
    }
    return (0);
}
