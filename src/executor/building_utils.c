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

    newline = 0;
    i = 0;
    if (command->full_cmd[1] == "-n")
    {
        newline = 1;
        while(command->next)
        {
            echo_output[i] = ft_strcpy(echo_output, command->full_cmd[i + 2]);
            i++;
        } 
    }
    else
    {
        i = 0;
        while(command->next)
        {
            echo_output[i] = ft_strcpy(echo_output, command->full_cmd[i + 1]);
            i++;
        } 
    }
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
    while(command->next)
    {
        if(command->full_cmd[0] == "exit" && command->next == NULL)
        {
            write (1, "exit\n", 5);
            exit(0);
        }
        else
        {
            if(command)
        }
        
    }
}
