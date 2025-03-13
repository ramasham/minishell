/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:23:23 by rsham             #+#    #+#             */
/*   Updated: 2025/03/13 16:16:51 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int validation(t_command *cmd, t_data *data)
{
    int  validation_result;

    validation_result = validate_cmd(data, cmd);
    if (validation_result == 1 || validation_result == CMD_NOT_FOUND 
            || validation_result == CMD_NOT_EXECUTABLE)
    {
        data->last_exit_status = validation_result;
        return (1);
    }
    return (0);
}

void    wait_for_children(t_data  *data, pid_t *pids, int cmd_count, int *exit_status)
{
    int i;
    int status;

    i = 0;
    while (i < cmd_count)
    {
        waitpid(pids[i], &status, 0);
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

static void handle_dup2(t_command *cmd, t_data *data, int *pipe_fd, int index)
{
    set_redi(cmd, data);
    if (cmd->heredoc_fd != -1 && cmd->infile == STDIN_FILENO && index > 0)
        dup2(pipe_fd[(index - 1) * 2], STDIN_FILENO);
    if (cmd->outfile == STDOUT_FILENO && index < data->cmd_count - 1)
        dup2(pipe_fd[(index * 2) + 1], STDOUT_FILENO);
}

int child_process(t_data *data, t_command *cmd, int *pipe_fd, int index) 
{
    handle_dup2(cmd, data, pipe_fd, index);
    if (ft_strcmp(cmd->full_cmd[0], "exit") == 0)
        ft_exit(cmd, data);
    if (built_ins(cmd, data))
        exit(data->last_exit_status);
    if (validation(cmd, data))
        exit(data->last_exit_status);
    
    execve(cmd->full_path, cmd->full_cmd, data->envp);
    perror("execve failed");
    cleanup_shell(data);
    exit(data->last_exit_status);
}


int create_children(t_data *data, int *pipe_fd, pid_t *pids)
{
    t_command *cmd;
    int i;
    
    i = 0;
    cmd = (*data->commands);
    while (cmd)
    {
        pids[i] = fork();
        if (pids[i] == -1)
        {
            perror("fork failed");
            free_list_cmd(data->commands);
            return(1);
        }
        if (pids[i] == 0)
        {
            if (child_process(data, cmd, pipe_fd, i))
            {
                free_list_cmd(data->commands);
                exit(1);
            }
        }
        cmd = cmd->next;
        i++;
    }
    return (0);
}