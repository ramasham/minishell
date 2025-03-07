/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <rsham@student.42amman.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:15:57 by marvin            #+#    #+#             */
/*   Updated: 2025/03/07 23:15:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//update env value
char *create_env_var(const char *name, const char *value)
{
    char *env_var;
    int len;

    len = ft_strlen(name) + ft_strlen(value) + 2;
    env_var = malloc(len);
    if (!env_var)
        return NULL;
    ft_strlcpy(env_var, name, len);
    ft_strlcat(env_var, "=", len);
    ft_strlcat(env_var, value, len);
    return env_var;
}

int update_env_var(char ***envp, const char *name, const char *value)
{
    int i;
    char *new_var;

    i = 0;
    while ((*envp)[i])
    {
        if (ft_strncmp((*envp)[i], name, ft_strlen(name)) == 0 && 
            (*envp)[i][ft_strlen(name)] == '=')
        {
            new_var = create_env_var(name, value);
            if (!new_var)
                return 1;
            free((*envp)[i]);
            (*envp)[i] = new_var;
            return 0;
        }
        i++;
    }
    new_var = create_env_var(name, value);
    if (!new_var)
        return 1;
    (*envp) = realloc(*envp, (i + 2) * sizeof(char *));
    if (!(*envp))
    {
        free(new_var);
        return 1;
    }
    (*envp)[i] = new_var;
    (*envp)[i + 1] = NULL;
    return 0;
}
