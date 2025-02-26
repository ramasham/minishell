/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:23:44 by laburomm          #+#    #+#             */
/*   Updated: 2025/02/26 12:24:06 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void export()
{
    //here it should appear all the env var in the programm
}

void unset()
{
    
}

void env(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        ft_printf("%s\n", env[i]);
        i++;
    }
}
