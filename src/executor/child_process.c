/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:23:23 by rsham             #+#    #+#             */
/*   Updated: 2025/04/15 18:49:23 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cleanup_child_exe(t_data *data)
{
    if (data->pipe_fd)
        free(data->pipe_fd);
    if (data->pids)
        free(data->pids);
    free_exec_cmd(*data->commands);
    free(data->commands);
    free_env(data->envp);
}
void cleanup_child(t_data *data)
{
    if (data->pipe_fd)
        free(data->pipe_fd);
    if (data->pids)
        free(data->pids);
    free_list_cmd(data->commands);
    free(data->commands);
    free_env(data->envp);
}

void    wait_for_children(t_data  *data, int cmd_count, int *exit_status)
{
    int i;
    int status;

    i = 0;    
    while (i < cmd_count)
    {
        if((*data->commands)->outfile_fd != -1)
            close((*data->commands)->outfile_fd);
        cleanup_redirections((*data->commands));
        signal(SIGINT, SIG_IGN);
        waitpid(data->pids[i], &status, 0);
        if (WIFEXITED(status))
        {
            *exit_status = WEXITSTATUS(status);
            if (*exit_status == 0)
                data->last_exit_status = 0;
        }
        else if (WIFSIGNALED(status))
        {
            *exit_status = 128 + WTERMSIG(status);
            if (WTERMSIG(status) == SIGQUIT)
                ft_putstr_fd("Quit (core dumped)\n", 2);
        }
        else
            *exit_status = 1;
        i++;
    }
}
static void	handle_execve_error(t_command *cmd, t_data *data)
{
	int	exit_code;

	if (errno == EACCES)
	{
		ft_putstr_fd(": Permission denied\n", 2);
		exit_code = 126;
    }
	else
	{
		perror(cmd->exe_cmd[0]);
		exit_code = 1;
	}
	cleanup_redirections(cmd);
	cleanup_child_exe(data);
	exit(exit_code);
}


static void	pre_exec_checks(t_command *cmd, t_data *data)
{
	struct stat	path_stat;

	if (stat(cmd->full_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd(cmd->exe_cmd[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		cleanup_redirections(cmd);
		cleanup_child_exe(data);
		exit(126);
	}
}

void	child_process(t_data *data, t_command *cmd)
{
	if (ft_strcmp(cmd->exe_cmd[0], "exit") == 0)
    {
		ft_exit(cmd, data);
    }
	get_cmd_path(cmd, data);
	if (!cmd->full_path)
	{
		cmd_not_found_msg(cmd);
		cleanup_child_exe(data);
		exit(127);
	}
	if (setup_redirections(cmd) != 0)
    {
        cleanup_redirections(cmd);
        cleanup_child_exe(data);
        exit(1);
    }
	if (cmd->outfile_fd != -1)
		close(cmd->outfile_fd);
	if (cmd->infile_fd != -1)
		close(cmd->infile_fd);
	cleanup_heredoc(cmd);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	pre_exec_checks(cmd, data);
	execve(cmd->full_path, cmd->exe_cmd, data->envp);
	handle_execve_error(cmd, data);
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

int forking(t_data *data, t_command *cmd, int i)
{

    data->pids[i] = fork();
    if (data->pids[i] == -1)
    {
        cleanup_child_exe(data);
        return(1);
    }
    if (data->pids[i] == 0)
    {
        setup_redirection(data, i);
        close_pipes(data, data->cmd_count);
        child_process(data, cmd);
    }
    return (0);
}

int setup_children(t_data *data)
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
