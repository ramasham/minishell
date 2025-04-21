/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:16:34 by rsham             #+#    #+#             */
/*   Updated: 2025/04/21 17:47:25 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_cmd_quotes(t_command *cmd)
{
	int		i;
	int		len;
	char	*arg;
	char	*trimmed;

	i = 0;
	while (cmd->exe_cmd && cmd->exe_cmd[i])
	{
		arg = cmd->exe_cmd[i];
		len = ft_strlen(arg);
		if ((arg[0] == '\'' && arg[len - 1] == '\'') || (arg[0] == '"' && arg[len - 1] == '"'))
		{
			if (arg[0] == '\'')
				trimmed = ft_strtrim(arg, "'");
			else
				trimmed = ft_strtrim(arg, "\"");
			if (trimmed)
			{
				free(cmd->exe_cmd[i]);
				cmd->exe_cmd[i] = trimmed;
			}
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
