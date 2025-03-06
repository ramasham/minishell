/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/06 22:36:20 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void    init_data(t_data *data)
{
    data->input = NULL;
    data->node = NULL;
    data->commands = NULL;
    // data->exit_status = 0;
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
    
    // setup_signal_handlers();
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
        setup_signal_handlers();
        if (isatty(STDIN_FILENO))
            data->input = readline("\033[1;35mminishell$\033[0m ");
        if (handle_eof(data->input))
            break;
        if (data->input[0] == '\0')
        {
            free(data->input);
            continue ;
        }
        if (!tokenizer(data))
        {
            expander(data);
            set_commands(data);
            executor(data);
        }
        data->last_exit_status = g_exit_status;
        if (*data->input)
            add_history(data->input);
        free(data->input);
    }
    return (0);
}
