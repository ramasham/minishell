#include "minishell.h"

static int init_node(t_data *data)
{
    if(!data->node)
    {
        data->node= malloc(sizeof(t_node));
        if (!data->node)
        {
            return (0);
            *(data->node) = NULL;
        }
        return (1);
    }
}

static void add_tokens(t_data *data, char *token)
{
    t_data *new_node;
    if (token && *token)
    {
        new_node = create_node(token);
        ft_nodeadd_back(data->node, new_node);
    }
}

void split_input(t_data *data)
{
    char *ptr;
    char *token;
    char i;
    int inside_qoutes_flag;

    i = 0;
    ptr = data->input;
    inside_qoutes_flag = 0;
    token = malloc(ft_strlen(data->input) + 1);
    if (!token || !init_node(data))
    {
        free (token);
        return;
    }
    inside_qoutes_flag = 0;
    while (*ptr) 
    {
        if (*ptr == '"' || *ptr == '\'')
        {
            inside_qoutes_flag = !inside_qoutes_flag;
            token[i++] = *ptr;
        }
        else if (*ptr == ' ' && !inside_qoutes_flag) 
        {
            token[i] = '\0';
            add_tokens(data, token);
        }
        else
            token[i++] = *ptr;
        ptr++;
    }
    if (i > 0)
    {
        token[i] = '\0';
        add_tokens(data, token);
    }
}
