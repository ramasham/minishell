/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsham <rsham@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:34:06 by laburomm          #+#    #+#             */
/*   Updated: 2025/02/18 19:57:46 by rsham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//create search_for_env function
//inside
//iterate through each node
//iterate through content
//if found -> save to buffer starting from $ to special char or space or operators
//send buffer to expander
//else nothing here

char *ft_strndup(const char *s, int n)
{
    char *dup;
    int i = 0;

    dup = (char *)malloc((n + 1) * sizeof(char));
    if (!dup)
        return NULL;
    while (i < n && s[i])
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return dup;
}

char *ft_strjoin_three(char *s1, char *s2, char *s3)
{
    char *temp = ft_strjoin(s1, s2);
    char *result;

    if (!temp)
        return (NULL);
    
    result = ft_strjoin(temp, s3);
    free(temp);
    return result;
}

void search_for_env(t_node *current_node, int *i, char **buffer)
{
    int start;

    start = *i + 1;
    (*i)++;
    while (current_node->content[*i] && 
          ((current_node->content[*i] >= 'A' && current_node->content[*i] <= 'Z') ||
           (current_node->content[*i] >= 'a' && current_node->content[*i] <= 'z') ||
           (current_node->content[*i] >= '0' && current_node->content[*i] <= '9') ||
           current_node->content[*i] == '_'))
    {
        (*i)++;
    }
    *buffer = ft_strndup(current_node->content + start, *i - start);
    if (!*buffer)
        *buffer = ft_strdup("");
}

void replace_in_content(t_node *current, char *buffer, int start, int end)
{
    char *new_content;
    char *before;
    char *after;

    before =ft_strndup(current->content, start);
    after = ft_strdup(current->content + end);
    if (!before || !after)
    {
        free(before);
        free(after);
        return;
    }
    new_content = ft_strjoin_three(before, buffer, after);
    free(current->content);
    free(before);
    free(after);
    current->content = new_content;
}

// void process_dollar(t_node *current, int *i, char **buffer)
// {
//     int start;
//     char *env_value;
    
//     start = *i;
//     search_for_env(current, i, buffer);
//     if (*buffer)
//     {
//         env_value = getenv(*buffer);
//         if (!env_value)
//             env_value = "";
//         replace_in_content(current, *buffer, start, *i);
//         *i = start + ft_strlen(env_value);
//         free(*buffer);
//         *buffer = NULL;
//     }
// }

// void expander_split(t_data *data)
// {
//     int i;
//     int j;
//     char *buffer;
//     t_node *current;
    
//     j = 0;
//     buffer = malloc(ft_strlen(data->input) + 1);
//     current = (*data->node);
//     while (current)
//     {
//         i = 0;
//         while (current->content[i])
//         {
//             if (current->content[i] == '$')
//             {
//                 j = i + 1;
//                 while (current->content != ' ') // need to adjust delimeters
//                     buffer[j++] = current->content[i++];
//                 process_dollar(current, &i, &buffer);
//             }
//             else
//                 i++;
//         }
//         current = current->next;
//     }
// }

void    process_dollar(char *buffer)
{
    if (!buffer)
        return;
    
}
void    expander_split(t_data *data)
{
    int i;
    int j;
    char    *buffer;
    t_node  *current;

    buffer = malloc(ft_strlen(data->input) + 1); //
    current = (*data->node);
    while (current)
    {
        while (current->content[i])
        {
            if (current->content[i] == '$')
            {
                j = i + 1;
                while (current->content[i] != ' ')
                {
                    buffer[j++] = current->content[i++]; 
                }
                process_dollar(buffer[j]);
            }
            i++;
        }
        current = current->next;
    }
}
