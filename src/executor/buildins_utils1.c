/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <rsham@student.42amman.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:23:46 by laburomm          #+#    #+#             */
/*   Updated: 2025/03/07 18:11:25 by marvin           ###   ########.fr       */
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

void ft_pwd(void)
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)))
    {
        write(1, cwd, ft_strlen(cwd));
        write(1, "\n", 1);
    }
    else
        perror("minishell: pwd");
}


void ft_cd(char *path)
{
    char cwd[1024];
    char old_cwd[1024];
    char *oldpwd;
    char *newpwd;

    if (!path)
    {
        path = getenv("HOME");
        if (!path)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
            return;
        }
    }
    if (!getcwd(old_cwd, sizeof(old_cwd)))
    {
        perror("minishell: cd");
        g_exit_status = 2;
        return;
    }
    if (chdir(path) != 0)
    {
        perror("minishell: cd");
        g_exit_status = 2;
        return;
    }
    if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("minishell: cd");
        g_exit_status = 2;
        return;
    }
    oldpwd = ft_strjoin("OLDPWD=", old_cwd);
    if (!oldpwd)
    {
        perror("minishell: cd");
        g_exit_status = 2;
        return;
    }
    newpwd = ft_strjoin("PWD=", cwd);
    if (!newpwd)
    {
        perror("minishell: cd");
        g_exit_status = 2;
        free(oldpwd);
        return;
    }
    setenv("OLDPWD", old_cwd, 1);
    setenv("PWD", cwd, 1);
    free(oldpwd);
    free(newpwd);
}
