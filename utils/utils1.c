/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:26:16 by rsham             #+#    #+#             */
/*   Updated: 2025/03/08 02:00:41 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     is_space(char c)
{
    return (c == ' ' || c == '\t');
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
