/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:23:44 by laburomm          #+#    #+#             */
/*   Updated: 2025/03/05 02:25:55 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void *new_ptr;

    if (!ptr)
        return malloc(new_size);
    if (!new_size)
    {
        free(ptr);
        return NULL;
    }
    new_ptr = malloc(new_size);
    if (!new_ptr)
    {
        free(ptr);
        return NULL;
    }
    size_t copy_size = old_size < new_size ? old_size : new_size;
    ft_memcpy(new_ptr, ptr, copy_size);

    free(ptr);
    return new_ptr;
}

static void print_env_sorted(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        ft_printf("declare -x %s\n", envp[i]);
        i++;
    }
}

static void add_new_var(t_data *data, char *var)
{
    int j;
    size_t old_size;
    char **new_envp;

    j = 0;
    old_size = 0;
    while (data->envp[old_size])
        old_size++;
    new_envp = ft_realloc(data->envp, old_size * sizeof(char *), (j + 2) * sizeof(char *));
    if (!new_envp)
    {
        perror("minishell: export");
        free(var); 
        return;
    }
    data->envp = new_envp;
    data->envp[j] = var;
    data->envp[j + 1] = NULL;
}

static void add_or_update_env(t_data *data, char *var)
{
    int j;

    j = 0;
    while (data->envp[j])
    {
        if (ft_strncmp(data->envp[j], var, ft_strchr(var, '=') - var) == 0)
        {
            free(data->envp[j]);
            data->envp[j] = var;
            return;
        }
        j++;
    }

    add_new_var(data, var);
}

void ft_export(t_data *data, t_command *command)
{
    int i;
    char *var;

    i = 1;
    if (!command->full_cmd[1])
    {
        print_env_sorted(data->envp);
        return;
    }
    while (command->full_cmd[i])
    {
        if (ft_strchr(command->full_cmd[i], '='))
        {
            var = ft_strdup(command->full_cmd[i]);
            if (!var)
            {
                perror("minishell: export");
                return;
            }
            add_or_update_env(data, var);
        }
        i++;
    }
}

