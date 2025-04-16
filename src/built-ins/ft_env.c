/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:23:46 by laburomm          #+#    #+#             */
/*   Updated: 2025/04/16 14:20:23 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **env)
{
	int	i;

	if (!env)
	{
		ft_putstr_fd("minishell: env: environment not found\n", 2);
		return ;
	}
	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '=') != NULL)
		{
			write(1, env[i], ft_strlen(env[i]));
			write(1, "\n", 1);
		}
		i++;
	}
}
