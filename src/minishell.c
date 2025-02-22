/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:12:02 by rsham             #+#    #+#             */
/*   Updated: 2025/02/22 21:20:01 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_data(t_data *data)
{
    data->input = NULL;
}

int main()
{
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
            get_commands(data, (*data->node));
            // handle_pipes((*data->node));
            // free(data->input);
            // free(data);
        }
        // else if (tokenizer(data) == 0)
        // {
        //     expander(data);
        // }
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
