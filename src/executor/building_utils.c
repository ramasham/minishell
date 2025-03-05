/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:23:46 by laburomm          #+#    #+#             */
/*   Updated: 2025/02/26 17:23:02 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void env(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        ft_printf("%s\n", env[i]);
        i++;
    }
}

void pwd(void)
{
    char *cwd;
    char *buffer[1024];

    cwd = getcwd(buffer, 1024);
    if (cwd)
        ft_printf("%s\n", cwd);
    else
        perror("pwd");
}

void echo(t_command *command)
{
    char **echo_output;
    int newline;
    int i;

    newline = 1;
    i = 1;
    if (command->full_cmd[1] && ft_strcmp(command->full_cmd[1] ,"-n") == 0)
    {
        newline = 0;
        i++;
    }
    while (command->full_cmd[i])
    {
        ft_printf("%s", command->full_cmd[i]);
        if (command ->full_cmd[i + 1])
            write(1, " ", 1);
        i++;
    }
    if(newline)
        write(1, "\n", 1);
}

void	ft_cd(char *path)
{
	if (!path)
	{
		printf("cd: missing argument\n");
		return;
	}
	if (chdir(path) != 0)
		perror("cd");
}

void ft_exit(t_command *command)
{
    int status;
    status = 0;
    if (command->full_cmd[1])
    {
        status = ft_atoi(command->full_cmd[1]);
        printf("exit\n");
        exit(status);
    }
    else
    {
        printf("exit\n");
        exit(0);
    }
}
