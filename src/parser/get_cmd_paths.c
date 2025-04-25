/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:41:39 by rsham             #+#    #+#             */
/*   Updated: 2025/04/23 17:24:39 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**find_path(t_data *data)
{
	int		i;
	char	**paths;

	i = 0;
	if (!data || !data->envp)
	{
		ft_putstr_fd("Error: envp is NULL\n", 2);
		return (NULL);
	}
	while (data->envp[i] && ft_strncmp(data->envp[i], "PATH=", 5) != 0)
		i++;
	if (!data->envp[i])
	{
		ft_error((*data->commands)->exe_cmd[0], "No such file or directory");
		cleanup_exe(data);
		return (NULL);
	}
	paths = ft_split(data->envp[i] + 5, ':');
	if (!paths || !paths[0])
	{
		free_2d(paths);
		return (NULL);
	}
	return (paths);
}

int	check_access(t_data *data, t_command *cmd, char *path)
{
	(void)data;
	if (!path)
		return (1);
	if (access(path, F_OK) == -1)
	{
		free(path);
		return (1);
	}
	if (access(path, X_OK) == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free(path);
		data->last_exit_status = CMD_NOT_EXECUTABLE;
		data->error = 1;
		return (CMD_NOT_EXECUTABLE);
	}
	if (cmd->full_path)
		free(cmd->full_path);
	cmd->full_path = ft_strdup(path);
	free(path);
	if (!cmd->full_path)
		return (1);
	return (0);
}

char	*join_path_cmd(char *path, char *cmd)
{
	char	*temp;
	char	*path_with_cmd;

	if (!path || !cmd)
	{
		printf("no path\n");
		return (NULL);
	}
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
	if (!path_with_cmd)
		return (NULL);
	return (path_with_cmd);
}

int	get_cmd_path(t_command *cmd, t_data *data)
{
	char	*path;
	char	**paths;
	int		i;

	paths = find_path(data);
	if (paths == NULL)
		return (2);
	if (get_abs_path(cmd, data))
		return (1);
	while (cmd)
	{
		i = -1;
		while (paths[++i])
		{
			path = join_path_cmd(paths[i], cmd->exe_cmd[0]);
			if (check_access(data, cmd, path) == 0)
			{
				free_2d(paths);
				return (0);
			}
		}
		cmd = cmd->next;
	}
	free_2d(paths);
	return (1);
}
