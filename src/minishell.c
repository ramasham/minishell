/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/05 00:49:14 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void    init_data(t_data *data)
{
    data->input = NULL;
    data->node = NULL;
    data->commands = NULL;
    data->exit_status = 0;
    data->envp = NULL;
}

// static void print_envp(char **envp)
// {
//     int i = 0;

//     while (envp && envp[i])
//     {
//         printf("envp[%d]: %s\n", i, envp[i]);
//         i++;
//     }
// }


int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    t_data  *data;
    
    
    data = malloc(sizeof(t_data));
    if (!data)
    {
        perror("");
        return (1);
    }
    init_data(data);
    data->envp = envp;
    while (1)
    {
        // init_data(data);
        if (isatty(STDIN_FILENO))
            data->input = readline("\033[1;35mminishell$\033[0m ");
        if (data->input[0] == '\0')
        {
            continue ;
        }
            if (tokenizer(data) == 0)
        {
            expander(data);
            set_commands(data);
            executor(data);
            // print_envp(data->envp);
            // free(data->input);
            // free(data);
        }
        if (data->input == NULL)
        {
            free(data->input);
            break;
        }
        if (*data->input)
            add_history(data->input);
        free(data->input);
    }
    return (0);
}
