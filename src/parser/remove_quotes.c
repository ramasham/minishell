/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:16:34 by rsham             #+#    #+#             */
/*   Updated: 2025/04/23 10:34:29 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void trim_cmd_quotes(t_command *cmd)
{
    int		i;
    char	*trimmed;

	i = 1;
    if (!cmd || !cmd->exe_cmd)
        return;
    while (cmd->exe_cmd[i])
    {
        trimmed = remove_quotes(cmd->exe_cmd[i]);
        if (trimmed)
        {
            free(cmd->exe_cmd[i]);
            cmd->exe_cmd[i] = trimmed;
        }
        i++;
    }
}

char	*remove_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	char	quote;

	quote = 0;
	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '"' || str[i] == '\''))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

void	remove_quotes_from_command(t_command *cmd)
{
	int		i;
	char	*stripped;

	if (!cmd || !cmd->exe_cmd)
		return ;
	i = 0;
	while (cmd->exe_cmd[i])
	{
		if (i == 0)
			stripped = remove_quotes(cmd->exe_cmd[i]);
		else if (cmd->exe_cmd[i])
			stripped = ft_strdup(cmd->exe_cmd[i]);
		else
			stripped = NULL;
		free(cmd->exe_cmd[i]);
		cmd->exe_cmd[i] = stripped;
		i++;
	}
}
