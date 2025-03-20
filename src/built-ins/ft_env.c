/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:23:46 by laburomm          #+#    #+#             */
/*   Updated: 2025/03/08 01:48:57 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_env(char **env)
{
    int i;

    if (!env)
    {
        ft_putstr_fd("minishell: env: environment not found\n", 2);
        return;
    }
    i = 0;
    while (env[i])
    {
        write(1, env[i], ft_strlen(env[i]));
        write(1, "\n", 1);
        i++;
    }
}
