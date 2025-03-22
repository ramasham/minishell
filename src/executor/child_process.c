/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:23:23 by rsham             #+#    #+#             */
/*   Updated: 2025/03/23 00:13:30 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    wait_for_children(t_data  *data, int cmd_count, int *exit_status)
{
    int i;
    int status;

    i = 0;
    while (i < cmd_count)
    {
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

void handle_dup2(t_command *cmd, t_data *data, int index)
{
    set_redi(cmd, data);
    if (cmd->heredoc_fd != -1 && cmd->infile == STDIN_FILENO && index > 0)
        dup2(data->pipe_fd[(index - 1) * 2], STDIN_FILENO);
    if (cmd->outfile == STDOUT_FILENO && index < data->cmd_count - 1)
        dup2(data->pipe_fd[(index * 2) + 1], STDOUT_FILENO);
}

int child_process(t_data *data, t_command *cmd, int index) 
{
    (void)cmd;
    handle_dup2((*data->commands), data, index);
    if (ft_strcmp((*data->commands)->full_cmd[0], "exit") == 0)
        ft_exit((*data->commands), data);
    get_cmd_path((*data->commands), data);
    if (check_path(data) != 0)
    {
        free(data->pipe_fd);
        free(data->pids);
        // free_list_cmd(&cmd);
        free_list_cmd(data->commands);
        free(data->commands);
        data->commands = NULL;
        exit(data->last_exit_status);
    }
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    execve((*data->commands)->full_path, (*data->commands)->full_cmd, data->envp);
    free(data->pipe_fd);;
    free(data->pids);
    exit(data->last_exit_status);
}


int  create_children(t_data *data)
{
    t_command *cmd;
    int i;
    
    i = 0;
    cmd = (*data->commands);
    while (cmd)
    {
        data->pids[i] = fork();
        if (data->pids[i] == -1)
        {
            perror("fork failed");
            free(data->pipe_fd);
            free(data->pids);
            free_list_cmd(data->commands);
            free(data->commands);
            data->commands = NULL;
            data->pipe_fd = NULL;
            data->pids = NULL;
            return(1);
        }
        if (data->pids[i] == 0)
        {
            if (i > 0)
                dup2(data->pipe_fd[(i - 1) * 2], STDIN_FILENO);
            if (i < data->cmd_count - 1)
                dup2(data->pipe_fd[i * 2 + 1], STDOUT_FILENO);
            close_pipes(data, data->cmd_count);
            if (child_process(data, cmd, i))
            {
                free(data->pids);
                free(data->pipe_fd);
                free_list_cmd(data->commands);
                free(data->commands);
                data->commands = NULL;
                exit(1);
            }
        }
        cmd = cmd->next;
        i++;
    }
    return (0);
}
