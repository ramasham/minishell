/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:12:21 by rsham             #+#    #+#             */
/*   Updated: 2025/02/26 19:00:36 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     get_cmd_no(t_command *cmds)
{
    int     size;
    if (cmds)
        size = ft_lstsize(cmds);
    return (size);
}

int   create_pipes(t_command *cmds, int num_cmds)
{
    int     pipes_fd[2 * (num_cmds - 1)];
    int     i;

    i = 0;
    while(i < num_cmds)
    {
        if (pipe(pipes_fd) == -1)
        {
            perror("pipe: ");
            return (-1);
        }
        i++;
    }
    return (0);
}
void    fork_and_execute(t_command *cmds)
{
    
}

void    execute_pipeline(t_command *cmds)
{
    int no_of_cmds;
    int i;

    i = 0;
    no_of_cmds = get_cmd_no(cmds);
    if (create_pipes(cmds, no_of_cmds))
    {
        ft_putstr_fd("error creating pipes\n", 2);
        return (1);
    }
    while (i < no_of_cmds)
    {
        fork_and_execute(cmds,)
    }
    
    
}

int     is_external(t_command *cmd, char **envp)
{
    if (get_cmd_path(cmd, envp) == 0)
        return (1);
    else
        return (0);
}

int     validate_cmd(t_command *cmds, char **envp)
{
    int multiple_cmds;
    
    multiple_cmds = 0;
    if (get_cmd_no(cmds) > 1)
        multiple_cmds = 1;
    if (built_ins(cmds, envp) && !multiple_cmds)
        execute_builtins(cmds);
    else if ((built_ins(cmds, envp) && multiple_cmds) || is_external(cmds, envp))
        execute_externals();
    else
    {
        ft_putstr_fd("command not found\n", 2);
        return (1);
    }
    return (0);
}

int     executor(t_command *cmds)
{
    if ()
}
/*
functtion to get #no of cmds -> pipes[2 * (num_cmds - 1)];
1- Create multiple pipes:
2- Fork multiple child processes:
3- Redirect input and output for each command:



if (is_buildins(cmd) && !multiple_cmds)
    execute_builin(cmd);
else
    fork_and_execute(cmd);

// fork_and_execute() -> 

fork_and_execute(cmd, envp)
{
    get_cmd_path()
    if (path)

    if (is_exit_command(cmd)) {
    if (is_in_pipeline(cmd)) {
        // Skip the exit command in the pipeline (don't fork a child)
        return;
    } else {
        // Execute exit in the parent shell (exit the program)
        exit(0);
    }       
}
*/