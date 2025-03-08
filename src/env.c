/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:24:59 by rsham             #+#    #+#             */
/*   Updated: 2025/03/08 17:24:59 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Finds the index of an environment variable in data->envp.
int find_env_var(t_data *data, const char *name, char **env_var, char **eq_pos)
{
    int i;
    
    i = 0;
    while (data->envp[i] != NULL)
    {
        *env_var = data->envp[i];
        *eq_pos = ft_strchr(*env_var, '=');
        if (*eq_pos != NULL && (size_t)(*eq_pos - *env_var) == ft_strlen(name) &&
            ft_strncmp(*env_var, name, *eq_pos - *env_var) == 0)
        {
            return (i);
        }
        i++;
    }
    return (-1);
}

//Creates a new environment variable string in "NAME=VALUE" format.
char *create_new_var(const char *name, const char *value)
{
    size_t name_len;
    size_t value_len;
    char *new_var;

    name_len = ft_strlen(name);
    value_len = ft_strlen(value);
    new_var = malloc(name_len + value_len + 2);
    if (!new_var)
        return (NULL);
    ft_memcpy(new_var, name, name_len);
    new_var[name_len] = '=';
    ft_memcpy(new_var + name_len + 1, value, value_len + 1);
    return (new_var);
}

//Updates an environment variable if it exists, or adds a new one if it doesn't.
int update_envp(t_data *data, int index, char *new_var)
{
    int i;

    if (index != -1)
        data->envp[index] = new_var;
    else
    {
        i = 0;
        while (data->envp[i] != NULL)
            i++;
        data->envp[i] = new_var;
        data->envp[i + 1] = NULL;
    }
    return (0);
}

//Adds or updates an environment variable.
int my_setenv(t_data *data, const char *name, const char *value, int overwrite)
{
    char *env_var;
    char *eq_pos;
    int index;
    char *new_var;

    if (!name || !value || name[0] == '\0' || ft_strchr(name, '=') != NULL)
        return (-1);
    index = find_env_var(data, name, &env_var, &eq_pos);
    if (index != -1 && !overwrite)
        return (0);
    new_var = create_new_var(name, value);
    if (!new_var)
        return (-1);
    return (update_envp(data, index, new_var));
}

//Updates OLDPWD (previous working directory) and PWD (current working directory).
void update_env_vars(t_data *data, char *oldpwd, char *newpwd)
{
    if (my_setenv(data, "OLDPWD", oldpwd, 1) != 0 ||
        my_setenv(data, "PWD", newpwd, 1) != 0)
    {
        perror("minishell: setenv");
    }
}
