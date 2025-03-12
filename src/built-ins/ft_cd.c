/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 01:51:22 by rsham             #+#    #+#             */
/*   Updated: 2025/03/12 10:07:43 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void cd_error(t_data *data, char *oldpwd)
{
    perror("minishell: cd");
    data->last_exit_status = 2;
    free(oldpwd);
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

static int get_current_directory(char **dir)
{
    char cwd[1024];

    if (!getcwd(cwd, sizeof(cwd)))
        return (0);
    *dir = ft_strdup(cwd);
	return (*dir != NULL);
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

void ft_cd(t_data *data, char *path)
{
    char *oldpwd;
    char *newpwd;

    if (set_home_path(data, &path))
        return ;
    if (!get_current_directory(&oldpwd))
        cd_error(data, NULL);
    if (chdir(path) != 0)
        return (cd_error(data, oldpwd));
    if (!get_new_directory(&newpwd))
        return (cd_error(data, oldpwd));
    update_env_vars(data, oldpwd, newpwd);
    free(oldpwd);
    free(newpwd);
    data->last_exit_status = 0;
}
