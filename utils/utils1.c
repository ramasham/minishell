/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:26:16 by rsham             #+#    #+#             */
/*   Updated: 2025/04/10 14:54:02 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     is_space(char c)
{
    return (c == ' ' || c == '\t');
}

int	is_space_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (!ft_strchr(SPACES, str[i]))
			return (0);
		i++;
	}
	return (1);
}

char *ft_strremove(char *str, const char *remove)
{
    char *result;
    char *ptr;
    int i;
    int j;

    if (!str || !remove)
        return (NULL);
    result = (char *)malloc(ft_strlen(str) + 1);
    if (!result)
        return (NULL);
    ptr = str;
    i = 0;
    j = 0;
    while (ptr[i])
    {
        if (ptr[i] != remove[0])
            result[j++] = ptr[i];
        i++;
    }
    result[j] = '\0';
    return (result);
}

void    cmd_not_found_msg(t_command *cmds)
{
    ft_putstr_fd(cmds->full_cmd[0], 2);
    ft_putstr_fd(": command not found\n", 2);
}

