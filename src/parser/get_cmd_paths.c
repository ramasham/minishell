/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:41:39 by rsham             #+#    #+#             */
/*   Updated: 2025/02/26 18:53:54 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_free(char    **str)
{
    int     i;
    
    i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

char    **find_path(char **envp)
{
    int         i;
    char    **paths;

    i = 0;
    while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
        i++;
    if (!envp[i])
        return (NULL);
    paths = ft_split(envp[i] + 5, ':');
    if (!paths)
        return (NULL);
    return (paths);+
}

int     check_access(t_command *cmd, char  *path)
{
    if (!path)
        return (1);
    if (access(path, X_OK) == 0)
    {
        cmd->full_path = ft_strdup(path);
        if (!cmd->full_path)
        {
            free(path);
            return (1);
        }
        free(path);
        return (0);
    }
    free(path);
    return (1);
}

char    *join_path_cmd(char  *path, char *cmd)
{
    char    *temp;
    char    *path_with_cmd;

    temp = ft_strjoin(path, "/");
    if (!temp)
        return (NULL);
    path_with_cmd = ft_strjoin(temp, cmd);
    if (!path_with_cmd)
    {
        free(temp);
        return (NULL);
    }
    free(temp);
    return (path_with_cmd);
}

int    get_cmd_path(t_command *cmd, char **envp)
{
    char    *path;
    char    **paths;
    int     i;
    
    paths = find_path(envp);
    if (!paths)
        return (1);
    while (cmd)
    {
        i = -1;
        while (paths[++i])
        {
            path = join_path_cmd(paths[i], cmd->full_cmd[0]);
            if (check_access(cmd, path) == 0)
            {
                ft_free(paths);
                return (0);
            }
        }
        cmd = cmd->next;
    }
    ft_free(paths);
    return (1);
}
