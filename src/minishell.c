/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/15 18:58:51 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	process_empty_input(char *input)
{
	if (!input)
		return (1);
	if (input[0] == '\0' || is_space_str(input))
	{
		free(input);
		return (1);
	}
	return (0);
}


static void	minishell_loop(t_data *data)
{
	data->error = 0;
	data->stop = 0;
	data->empty = 0;
	g_exit_status = 0;
	if (!tokenizer(data))
	{
		expander(data);
		if (set_commands(data))
		{
			return;
		}
		if (data->commands && data->commands[0] &&
			ft_strcmp(data->commands[0]->exe_cmd[0], "exit") == 0)
		{
			ft_exit(data->commands[0], data);
		}
		executor(data);
	}
	if (*data->input && data->input)
		add_history(data->input);
	free(data->input);
	data->input = NULL;
}



int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_data	data;
	
	if (init_shell(&data, envp))
		return (1);
	while (1)
	{
		setup_signal_handlers();
		if (isatty(STDIN_FILENO))
			data.input = readline("\033[1;35mminishell$\033[0m ");
		if (handle_eof(data.input))
			break ;
		if (g_exit_status == 130 || g_exit_status == 131)
		{
			data.last_exit_status = g_exit_status;
			g_exit_status = 0;
		}
        if (process_empty_input(data.input))
			continue ;
		minishell_loop(&data);
	}
	cleanup_shell(&data);
	return (0);
}
