/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 02:06:43 by laburomm          #+#    #+#             */
/*   Updated: 2025/04/21 16:35:41 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void remove_env_var(t_data *data, char *var)
{
    int	j;
    int	k;
	
	j = 0;
	k = 0;
    while (data->envp[j])
    {
        if (ft_strncmp(data->envp[j], var, ft_strlen(var)) == 0 && data->envp[j][ft_strlen(var)] == '=')
        {
            free(data->envp[j]);
            k = j;
            while (data->envp[k])
            {
                data->envp[k] = data->envp[k + 1];
                k++;
            }
            break;
        }
        j++;
    }
}

void	ft_unset(t_data *data, t_command *command)
{
	int	i;

	i = 1;
	if (!command->exe_cmd[1])
		return ;
	while (command->exe_cmd[i])
	{
		remove_env_var(data, command->exe_cmd[i]);
		i++;
	}
	data->last_exit_status = 0;
}
