/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laburomm <laburomm@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 03:48:20 by laburomm          #+#    #+#             */
/*   Updated: 2025/03/24 01:41:20 by laburomm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Write a line to the pipe
void	write_heredoc_to_pipe(char *line, int pipe_fd[2])
{
	if (!line || !pipe_fd)
		return ;
	if (write(pipe_fd[1], line, ft_strlen(line)) == -1)
		perror("minishell: write");
	free(line);
}

// Check if the delimiter is quoted
int	is_quoted_delimiter(char *delimiter)
{
	if (delimiter[0] == '\'' || delimiter[0] == '"')
		return (0);  // It's quoted
	return (1);  // It's unquoted
}

// Check if the input line matches the delimiter
int	process_delimiter(char *line, char *delimiter)
{
	size_t	delim_len;
	size_t	line_len;

	if (!line || !delimiter)
		return (0);
	delim_len = ft_strlen(delimiter);
	line_len = ft_strlen(line);
	if (line_len == 0 || line_len - 1 != delim_len)
		return (0);
	return (ft_strncmp(line, delimiter, delim_len) == 0);
}

void	free_node(t_node *node)
{
	if (node)
	{
		if (node->content)
			free(node->content);
		free(node);
	}
}

// Handle backslashes in heredoc content
char	*handle_backslashes(char *line)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!line)
		return (NULL);
	result = malloc(ft_strlen(line) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\\')
		{
			if (line[i + 1] == '$' || line[i + 1] == '`' || 
				line[i + 1] == '"' || line[i + 1] == '\\' || 
				line[i + 1] == '\n')
			{
				result[j++] = line[++i];
				i++;
				continue;
			}
		}
		result[j++] = line[i++];
	}
	result[j] = '\0';
	return (result);
}

// Expand the heredoc line if necessary
char	*expand_heredoc_line(char *line, t_data *data)
{
	t_node	*current_node;
	char	*expanded_line;

	if (!line || !data)
		return (NULL);
	current_node = create_node(line);
	if (!current_node || process_node(current_node, data))
	{
		free(line);
		free_node(current_node);
		return (NULL);
	}
	expanded_line = ft_strdup(current_node->content);
	free_node(current_node);
	return (expanded_line);
}
