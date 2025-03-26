/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:48:26 by laburomm          #+#    #+#             */
/*   Updated: 2025/03/27 02:46:20 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    cleanup_heredoc(t_data *data)
{
    if (data->heredoc_fd != -1)
    {
        close(data->heredoc_fd);
        data->heredoc_fd = -1;
    }
    if (data->heredoc_delimiter)
    {
        free(data->heredoc_delimiter);
        data->heredoc_delimiter = NULL;
    }
}

static char	*get_clean_delimiter(char *delimiter, int *expand)
{
	char	*clean;

	*expand = 1;
	if (delimiter[0] == '\'' || delimiter[0] == '"')
	{
		*expand = (delimiter[0] == '\'');
		clean = ft_strtrim(delimiter, "\"'");
	}
	else
		clean = ft_strdup(delimiter);
	return (clean);
}

static int	write_heredoc_content(int pipe_fd, t_data *data, int expand)
{
	char	*line;
	char	*clean_line;
	size_t	len;

	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strcmp(line, data->heredoc_delimiter) == 0)
		{
			free(line);
			break ;
		}
		if (expand)
		{
			clean_line = expand_heredoc_line(line, data);
			write(pipe_fd, clean_line, ft_strlen(clean_line));
			free(clean_line);
		}
		else
			write(pipe_fd, line, ft_strlen(line));
		write(pipe_fd, "\n", 1);
		free(line);
	}
	return (0);
}

int	handle_heredoc(char *delimiter, t_data *data)
{
	int		pipe_fd[2];
	int		expand;
	char	*clean_delimiter;

	clean_delimiter = get_clean_delimiter(delimiter, &expand);
	if (!clean_delimiter)
		return (-1);
	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		free(clean_delimiter);
		return (-1);
	}
	data->heredoc_delimiter = clean_delimiter;
	write_heredoc_content(pipe_fd[1], data, expand);
	close(pipe_fd[1]);
	free(clean_delimiter);
	data->heredoc_delimiter = NULL;
	return (pipe_fd[0]);
}