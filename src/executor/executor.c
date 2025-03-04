/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:12:21 by rsham             #+#    #+#             */
/*   Updated: 2025/03/04 00:34:58 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     count_commnads(t_command *cmds)
{
    int i;

    i = 0;
    if (!cmds)
        return (0);
    while (cmds)
    {
        i++;
        cmds = cmds->next;
    }
    return (i);
}

// int     is_external(t_command *cmd, t_data *data)
// {
//     if (get_cmd_path(cmd, data) == 0)
//         return (1);
//     else
//         return (0);
// }

// int     validate_cmd(t_data *data, t_command *cmds, char **envp)
// {
//     int multiple_cmds;
    
//     multiple_cmds = 0;
//     if (get_cmd_no(cmds) > 1)
//     multiple_cmds = 1;
//     if (built_ins(cmds, envp) && !multiple_cmds)
//         execute_builtins(cmds);
//     else if ((built_ins(cmds, envp) && multiple_cmds) || is_external(cmds, envp))
//         executor(data);
//     else
//     {
//         ft_putstr_fd("command not found\n", 2);
//         return (1);
//     }
//     return (0);
// }


void piping(t_data *data, int **pipe_fd)
{
    int i;

    *pipe_fd = malloc(sizeof(int) * 2 * (data->cmd_count - 1));
    if (!*pipe_fd)
        exit(1);
    i = 0;
    while (i < data->cmd_count - 1)
    {
        if (pipe(*pipe_fd + (i * 2)) == -1)
        {
            perror("pipe");
            exit(1);
        }
        i++;
    }
}
int is_redirection(t_command *cmd)
{
    int i;

    i = 0;
    while (cmd->full_cmd[i])
    {
        if (ft_strcmp(cmd->full_cmd[i], ">") == 0)
            return (1);
        else if (ft_strcmp(cmd->full_cmd[i], "<") == 0)
            return (1);
        i++;
    }
    return (0);
}
void child_process(t_data *data, t_command *cmd, int *pipe_fd, int index) 
{
    int i;

    i = 0;
    set_redi(cmd);
    if (cmd->heredoc_fd == -1)
    {
        if (cmd->infile == STDIN_FILENO && index > 0)
            dup2(pipe_fd[(index - 1) * 2], STDIN_FILENO);
    }
    // if (cmd->infile == STDIN_FILENO && index > 0)
    //     dup2(pipe_fd[(index - 1) * 2], STDIN_FILENO);
    if (cmd->outfile == STDOUT_FILENO && index < data->cmd_count - 1)
        dup2(pipe_fd[(index * 2) + 1], STDOUT_FILENO);
    while (i < 2 * (data->cmd_count - 1))
        close(pipe_fd[i++]);

    if (execve(cmd->full_path, cmd->full_cmd, data->envp) == -1) 
    {
        perror("execve child process");
        exit(127);
    }
}


void create_children(t_data *data, int *pipe_fd, pid_t *pids)
{
    t_command *cmd;
    int i = 0;

    cmd = (*data->commands);
    while (cmd)
    {
        pids[i] = fork();
        if (pids[i] == 0)
            child_process(data, cmd, pipe_fd, i);
        cmd = cmd->next;
        i++;
    }
}

void close_pipes(int *pipe_fd, int cmd_count)
{
    int i = 0;

    while (i < 2 * (cmd_count - 1))
        close(pipe_fd[i++]);
}

void executor(t_data *data)
{
    int *pipe_fd;
    pid_t *pids;
    int i = 0;

    data->cmd_count = count_commnads(*data->commands);
    if (data->cmd_count == 0)
        return;
    pids = malloc(sizeof(pid_t) * data->cmd_count);
    if (!pids)
        exit(1);
    piping(data, &pipe_fd);
    create_children(data, pipe_fd, pids);
    close_pipes(pipe_fd, data->cmd_count);
    while (i < data->cmd_count)
        waitpid(pids[i++], NULL, 0);
    free(pipe_fd);
    free(pids);
}
