/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <rsham@student.42amman.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 23:03:31 by rsham             #+#    #+#             */
/*   Updated: 2025/03/07 23:53:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status;

// handles SIGINT (CTRL+C)
void handle_sigint(int sig) 
{
    (void)sig;
    write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
    g_exit_status = 130;
}

void handle_sigquit(int sig)
{
    (void)sig;
    g_exit_status = 131;
}

int handle_eof(char *input)
{
    if (input == NULL)
    {
        write(1, "exit\n", 5);
        return 1;
    }
    return 0;
}

void setup_signal_handlers()
{
    struct sigaction sa;

    // Handle SIGINT (CTRL+C)
    sa.sa_handler = &handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);

    // Handle SIGQUIT (CTRL+\) 
    sa.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa, NULL);
}