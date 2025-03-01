/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/03/01 16:30:03 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "minishell.h"

void    init_data(t_data *data)
{
    data->input = NULL;
    data->node = NULL;
    data->commands = NULL;
    data->exit_status = 0;
    data->envp = environ;
}

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
    while (1)
    {
        init_data(data);
        if (isatty(STDIN_FILENO))
            data->input = readline("\033[1;35mminishell$\033[0m ");
        if (tokenizer(data) == 0)
        {
            expander(data);
            set_commands(data, envp);
            executor(data);
            // free(data->input);
            // free(data);
        }
        if (data->input == NULL || ft_strcmp(data->input, "exit") == 0)
        {
            printf("exit\n");
            free(data->input);
            break;
        }
        if (*data->input)
            add_history(data->input);
        free(data->input);
    }
    return (0);
}
