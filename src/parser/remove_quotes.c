/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:16:34 by rsham             #+#    #+#             */
/*   Updated: 2025/04/17 19:51:02 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(const char *str, int remove_all)
{
	char	*result;
	int		i, j;
	char	quote = 0;
	(void)remove_all;
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
			stripped = remove_quotes(cmd->exe_cmd[i], 1);
		else if (cmd->exe_cmd[i])
			stripped = ft_strdup(cmd->exe_cmd[i]);
		else
			stripped = NULL;
		free(cmd->exe_cmd[i]);
		cmd->exe_cmd[i] = stripped;
		i++;
	}
}
