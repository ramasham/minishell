/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:12:02 by rsham             #+#    #+#             */
/*   Updated: 2025/02/15 17:39:00 by rsham            ###   ########.fr       */
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
        if (isatty(STDIN_FILENO))
            data->input = readline("\033[1;35mminishell$\033[0m ");
        tokenizer(data);
        if (data->input == NULL || ft_strcmp(data->input, "exit") == 0)
        {
            printf("exit\n");
            free(data->input);
            break;
        }
        if (*data->input)
            add_history(data->input);
        free(data->input);
        // rl_replace_line("", 0);
        // rl_on_new_line();
        // rl_redisplay();
    }
    return (0);
}
