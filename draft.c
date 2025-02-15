
// TokenType find_cmd(const char *token)
// {
//     // first cmd
//     int i = 0;
//     int flag = 0;
//     while ((token[i]))
//     {
//         if ((token[0] >= 'a' && token[0] <= 'z'))
//             flag = 1;
//         else
//             flag = 0;
//         i++;
//     }
//     printf("flag : %d\n", flag);
//     if (flag == 1)
//         return (CMD);
//     else
//         return (-1);
    
// }

// int handle_double_qoutes(char *token)
// {
//     char *start_q;
//     char *end_q;
//     int len = 0;
//     int flag = 0;
//     char *tmp_q;

//     if (start_q = ft_strchr(token, '"'))
//     {
//         flag = 1;
//         end_q = ft_strrchr(token, '"');
//     }
//     else
//         return (0);
//     len = end_q - start_q + 1;
//     tmp_q = malloc(len + 1);
//     strncpy(tmp_q, start_q + 1, len);
//     tmp_q[len] = '\0';
//     return (flag);
// }

// void    trim_operators(t_data *data)
// {
//     t_node  *current = *(data->node);
//     t_node  *new_node = NULL;
//     t_node  **new_lst = malloc(sizeof(t_node));
    
//     while (current)
//     {
//         if (ft_strncmp(current->content, ">>", 2) == 0)
//             new_node = create_node(">>");
//         else if (ft_strncmp(current->content, "<<", 2) == 0)
//             new_node = create_node("<<");
//         else if (ft_strncmp(current->content, ">", 1) == 0)
//             new_node = create_node(">");
//         else if (ft_strncmp(current->content, "<", 1) == 0)
//             new_node = create_node("<");
//         ft_nodeadd_back(new_lst, new_node);
//         current = current->next;
//     }
//     // data->node = new_lst;
//     // print_list(*(data->node));
// }

// void    trim_pipe(t_data *data)
// {
//     t_node  *current = *(data->node);
//     t_node  *new_node;
//     t_node  **new_lst;
//     char    *token;
//     char    *copy;

//     copy = NULL;
//     token = NULL;
//     new_node = NULL;
//     new_lst = malloc(sizeof(t_node));
//     if (!new_lst)
//         return;
//     *new_lst = NULL;
//     while (current)
//     {
//         copy = ft_strdup(current->content);
//         if (!copy)
//         {
//             current = current->next;
//             continue;
//         }
//         token = strtok(copy, "|");
//         while (token)
//         {
//             new_node = create_node(token);
//             ft_nodeadd_back(new_lst, new_node);
//             token = strtok(NULL, "|");
//         }
//         if (ft_strchr(current->content, '|'))
//             ft_nodeadd_back(new_lst, create_node("|"));
//         free(copy);
//         current = current->next;
//     }
//     *(data->node) = *new_lst;
// }


