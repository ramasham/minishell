/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:51:22 by rsham             #+#    #+#             */
/*   Updated: 2025/03/08 03:20:25 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cd [no args] -> home dir

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

static int my_setenv(t_data *data, const char *name, const char *value,
    int overwrite)
{
    int i;
    char *env_var;
    char *eq_pos;
    size_t name_len;
    size_t value_len;
    char *new_var;

    if (!name || !value || name[0] == '\0')
        return (-1);
    if (strchr(name, '=') != NULL)
        return (-1);

    i = 0;
    while (data->envp[i] != NULL)
    {
        env_var = data->envp[i];
        eq_pos = strchr(env_var, '=');
        if (eq_pos != NULL && (size_t)(eq_pos - env_var) == strlen(name) &&
            strncmp(env_var, name, eq_pos - env_var) == 0)
        {
            if (!overwrite)
                return (0);
            name_len = strlen(name);
            value_len = strlen(value);
            new_var = malloc(name_len + value_len + 2);
            if (!new_var)
                return (-1);
            memcpy(new_var, name, name_len);
            new_var[name_len] = '=';
            memcpy(new_var + name_len + 1, value, value_len + 1);
            data->envp[i] = new_var;
            return (0);
        }
        i++;
    }
    name_len = strlen(name);
    value_len = strlen(value);
    new_var = malloc(name_len + value_len + 2);
    if (!new_var)
        return (-1);
    memcpy(new_var, name, name_len);
    new_var[name_len] = '=';
    memcpy(new_var + name_len + 1, value, value_len + 1);
    data->envp[i] = new_var;
    data->envp[i + 1] = NULL;
    return (0);
}

static void cd_error(t_data *data)
{
    perror("minishell: cd");
    data->last_exit_status = 2;
    return ;
}

void ft_cd(t_data *data, char *path)
{
    char cwd[1024];
    char *oldpwd;
    char *newpwd;

    if (!path)
    {
        path = getenv("HOME");
        if (!path)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
            return ;
        }
    }
    if (!getcwd(cwd, sizeof(cwd)))
    {
        cd_error(data);
        return ;
    }
    oldpwd = ft_strdup(cwd);
    if (!oldpwd)
    {
        cd_error(data);
        return ;
    }
    if (chdir(path) != 0)
    {
        perror("minishell: cd");
        data->last_exit_status = 2;
        free(oldpwd);
        return ;
    }
    if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("minishell: cd");
        data->last_exit_status = 2;
        free(oldpwd);
        return ;
    }
    newpwd = ft_strdup(cwd);
    if (!newpwd)
    {
        perror("minishell: cd");
        data->last_exit_status = 2;
        free(oldpwd);
        return ;
    }
    my_setenv(data, "OLDPWD", oldpwd, 1);
    my_setenv(data, "PWD", newpwd, 1);
    free(oldpwd);
    free(newpwd);
}
