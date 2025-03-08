/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:51:22 by rsham             #+#    #+#             */
/*   Updated: 2025/03/08 06:06:42 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int validate_input_cd(const char *name, const char *value)
{
    if (!name || !value || name[0] == '\0')
        return (-1);
    if (strchr(name, '=') != NULL)
        return (-1);
    return (0);
}

static int find_env_var(t_data *data, const char *name, char **env_var, char **eq_pos)
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

static char *create_new_var(const char *name, const char *value)
{
    size_t name_len = ft_strlen(name);
    size_t value_len = ft_strlen(value);
    char *new_var = malloc(name_len + value_len + 2);
    if (!new_var)
        return (NULL);
    ft_memcpy(new_var, name, name_len);
    new_var[name_len] = '=';
    ft_memcpy(new_var + name_len + 1, value, value_len + 1);
    return (new_var);
}

static int update_envp(t_data *data, int index, char *new_var)
{
    if (index != -1)
    {
        // free(data->envp[index]);
        data->envp[index] = new_var;
    }
    else
    {
        int i = 0;
        while (data->envp[i] != NULL)
            i++;
        data->envp[i] = new_var;
        data->envp[i + 1] = NULL;
    }
    return (0);
}

static int my_setenv(t_data *data, const char *name, const char *value, int overwrite)
{
    char *env_var;
    char *eq_pos;
    int index;
    char *new_var;

    if (validate_input_cd(name, value) == -1)
        return (-1);
    index = find_env_var(data, name, &env_var, &eq_pos);
    if (index != -1 && !overwrite)
        return (0);
    new_var = create_new_var(name, value);
    if (!new_var)
        return (-1);
    return (update_envp(data, index, new_var));

}

static void cd_error(t_data *data)
{
    perror("minishell: cd");
    data->last_exit_status = 2;
    return ;
}

static int set_home_path(t_data *data, char **path)
{
    if (!*path)
    {
        *path = getenv("HOME");
        if (!*path)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
            data->last_exit_status = 1;
            return (1);
        }
    }
    return (0);
}

static int get_current_directory(char **oldpwd)
{
    char cwd[1024];

    if (!getcwd(cwd, sizeof(cwd)))
        return (0);
    *oldpwd = ft_strdup(cwd);
    if (!*oldpwd)
        return (0);
    return (1);
}

static int change_directory(char *path)
{
    if (chdir(path) != 0)
        return (0);
    return (1);
}

static int get_new_directory(char **newpwd)
{
    char cwd[1024];

    if (!getcwd(cwd, sizeof(cwd)))
        return (0);
    *newpwd = ft_strdup(cwd);
    if (!*newpwd)
        return (0);
    return (1);
}

static void update_env_vars(t_data *data, char *oldpwd, char *newpwd)
{
    if (my_setenv(data, "OLDPWD", oldpwd, 1) != 0 ||
        my_setenv(data, "PWD", newpwd, 1) != 0)
    {
        perror("minishell: setenv");
    }
}

void    cd_error_free(t_data *data, char *oldpwd)
{
    perror("minishell: cd");
    data->last_exit_status = 2;
    free(oldpwd);
    return ;
}
void ft_cd(t_data *data, char *path)
{
    char *oldpwd;
    char *newpwd;

    if (set_home_path(data, &path))
        return ;
    if (!get_current_directory(&oldpwd))
    {
        cd_error(data);
        return ;
    }
    if (!change_directory(path))
    {
        cd_error_free(data, oldpwd);
        return ;
    }
    if (!get_new_directory(&newpwd))
    {
        cd_error_free(data, oldpwd);
        return ;
    }
    update_env_vars(data, oldpwd, newpwd);
    free(oldpwd);
    free(newpwd);
    data->last_exit_status = 0;
}
