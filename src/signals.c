/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 23:03:31 by rsham             #+#    #+#             */
/*   Updated: 2025/03/20 21:47:35 by rsham            ###   ########.fr       */
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
    ft_putstr_fd("Quit (core dumped)\n", 2);
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

    sa.sa_handler = &handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    sa.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa, NULL);
}
