/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:16:34 by rsham             #+#    #+#             */
/*   Updated: 2025/04/16 14:49:46 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_outer_quotes(const char *str, int *i)
{
	while (str[*i] == '"' || str[*i] == '\'')
		(*i)++;
}

static int	copy_without_quotes(const char *src, char *dst, int i)
{
	int	j;

	j = 0;
	while (src[i])
	{
		if (src[i] != '"' && src[i] != '\'')
			dst[j++] = src[i];
		i++;
	}
	while (j > 0 && (dst[j - 1] == '"' || dst[j - 1] == '\''))
		j--;
	return (j);
}

static char	*remove_quotes(const char *str, int remove_all)
{
	char	*result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	if (remove_all)
	{
		skip_outer_quotes(str, &i);
		j = copy_without_quotes(str, result, i);
	}
	else
	{
		if (str[i] == '"' || str[i] == '\'')
			i++;
		j = 0;
		while (str[i])
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

void	remove_quotes_from_command(t_command *cmd)
{
	int		i;
	char	*stripped;

	if (!cmd || !cmd->full_cmd)
		return ;
	i = 0;
	while (cmd->full_cmd[i])
	{
		if (i == 0)
			stripped = remove_quotes(cmd->full_cmd[i], 1);
		else if (cmd->full_cmd[i])
			stripped = ft_strdup(cmd->full_cmd[i]);
		else
			stripped = NULL;
		free(cmd->full_cmd[i]);
		cmd->full_cmd[i] = stripped;
		i++;
	}
}
