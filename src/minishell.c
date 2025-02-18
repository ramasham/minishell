/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:12:02 by rsham             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/18 10:20:47 by laburomm         ###   ########.fr       */
=======
/*   Updated: 2025/02/17 19:32:58 by rsham            ###   ########.fr       */
>>>>>>> 6ab5488 (working on expander)
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_data(t_data *data)
{
    data->input = NULL;
}

int main(int argc, char **argv)
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
        tokenizer(data);
        expander(data);
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
