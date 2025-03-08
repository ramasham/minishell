
#include "minishell.h"



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


// void    check_redirection(t_data *data)
// {
//     char    *operators;
//     char    *ptr;
//     int     i;
//     int     j;

//     i = 0;
//     j = 0;
//     operators = "<>|";
//     ptr = data->input;
//     while (ptr[i])
//     {
//         if (ft_strchr(operators, ptr[i]))
//         {
//             j = i + 1;
//             while (ptr[j] && is_space(ptr[j]))
//                 j++;
//             if (ptr[j] && ft_strchr(operators, ptr[j]))
//             {
//                if (!((ptr[i] == '>' && ptr[i + 1] == '>') || 
//                       (ptr[i] == '<' && ptr[i + 1] == '<')))
//                 {
//                     ft_putstr_fd("Syntax error: Invalid redirection\n", 2);
//                     exit(1);
//                 }
//             }
//             i = j;
//         }
//         else
//             i++;
//     }
// }


// void trim_operators(t_data *data)
// {
//     t_node  *current;
//     t_node  *new_node;
//     t_node  **new_lst;
//     char    *token;
//     char    *delimiters;
//     char    *copy;

//     delimiters = " |><";
//     current = *(data->node);
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
//             ft_putstr_fd("allocation failed", 2);
//             exit(1);
//         }
//         if (current->type != DQUOTES && current->type != SQUOTES)
//         {
//             token = strtok(copy, delimiters);
//             while (token)
//             {
//                 new_node = create_node(token);
//                 ft_nodeadd_back(new_lst, new_node);
//                 token = strtok(NULL, delimiters);
//             }
//         }
//         else
//         {
//             new_node = create_node(copy);
//             ft_nodeadd_back(new_lst, new_node);
//         }
//         if (current->type != DQUOTES && current->type != SQUOTES)
//         {
//             if (ft_strchr(current->content, '|'))
//                 ft_nodeadd_back(new_lst, create_node("|"));
//             else if (ft_strncmp(current->content, ">>", 2) == 0)
//                 ft_nodeadd_back(new_lst, create_node(">>"));
//             else if (ft_strncmp(current->content, "<<", 2) == 0)
//                 ft_nodeadd_back(new_lst, create_node("<<"));
//             else if (ft_strchr(current->content, '>'))
//                 ft_nodeadd_back(new_lst, create_node(">"));
//             else if (ft_strchr(current->content, '<'))
//                 ft_nodeadd_back(new_lst, create_node("<"));
//         }
//         free(copy);
//         current = current->next;
//     }
//     *(data->node) = *new_lst;
//     free(new_lst);
// }


// void    split_input(t_data *data) 
// {
//     char    *ptr;
//     char    *token;
//     int     i;
//     int     inside_quotes;
//     t_node  *new_node;

//     i = 0;
//     ptr = data->input;
//     inside_quotes = 0;
//     new_node = NULL;
//     token = malloc(ft_strlen(data->input) + 1);
//     data->node = malloc(sizeof(t_node *));
//     if (!data->node)
//         return;
//     *data->node = NULL;
//     while (*ptr) 
//     {
//         if (*ptr == '"' || *ptr == '\'')
//         {
//             inside_quotes = !inside_quotes;
//             token[i++] = *ptr;
//         }
//         else if (*ptr == ' ' && !inside_quotes) 
//         {
//             if (i > 0) 
//             {
//                 token[i] = '\0';
//                 new_node = create_node(token);
//                 ft_nodeadd_back(data->node, new_node);
//                 i = 0;
//             }
//         }
//         else
//             token[i++] = *ptr;
//         ptr++;
//     }
//     if (i > 0)
//     {
//         token[i] = '\0';
//         new_node = create_node(token);
//         ft_nodeadd_back(data->node, new_node);
//     }
// }

//old trim_operator


// void	add_token(t_node **new_lst, char *token)
// {
// 	t_node	*new_node;

// 	new_node = create_node(token);
// 	ft_nodeadd_back(new_lst, new_node);
// }

// void	process_token(t_node **new_lst, t_node *current, char *delimiters)
// {
// 	char	*copy;
// 	char	*token;

// 	copy = ft_strdup(current->content);
// 	if (!copy)
// 	{
// 		ft_putstr_fd("allocation failed", 2);
// 		exit(1);
// 	}
// 	if (current->type == DQUOTES || current->type == SQUOTES)
// 		add_token(new_lst, copy);
// 	else
// 	{
// 		token = strtok(copy, delimiters);
// 		while (token)
// 		{
// 			add_token(new_lst, token);
// 			token = strtok(NULL, delimiters);
// 		}
// 	}
// 	free(copy);
// }

// void	process_operators(t_node **new_lst, char *content)
// {
// 	if (ft_strchr(content, '|'))
// 		add_token(new_lst, "|");
// 	else if (ft_strncmp(content, ">>", 2) == 0)
// 		add_token(new_lst, ">>");
// 	else if (ft_strncmp(content, "<<", 2) == 0)
// 		add_token(new_lst, "<<");
// 	else if (ft_strchr(content, '>'))
// 		add_token(new_lst, ">");
// 	else if (ft_strchr(content, '<'))
// 		add_token(new_lst, "<");
// }

// void	trim_operators(t_data *data)
// {
// 	t_node	*current;
// 	t_node	**new_lst;
// 	char	*delimiters = " |><";

// 	current = *(data->node);
// 	new_lst = malloc(sizeof(t_node *));
// 	if (!new_lst)
// 		return;
// 	*new_lst = NULL;
// 	while (current)
// 	{
// 		process_token(new_lst, current, delimiters);
// 		if (current->type != DQUOTES && current->type != SQUOTES)
// 			process_operators(new_lst, current->content);
// 		current = current->next;
// 	}
// 	*(data->node) = *new_lst;
// 	free(new_lst);
// }

// split_input -> linked_list 
// linked list -> should store the operators in nodes
// void    split_operators(t_data *data)
// {
//     t_node *current;
//     t_node  *new_lst;
//     char    *token;
//     t_node *new_node;
//     int i;
//     int j;

//     j = 0;
//     i = 0;
//     current = *(data->node);
//     new_lst = malloc(sizeof(t_node *));
//     if (!new_lst)
//         return;
//     new_lst = NULL;
//     while (current)
//     {
        
//         while (current->content[i] != '|' || current->content[i] != '>'
//              || current->content != '<')
//         {
//             token[j++] = current->content[i++];
//             new_node = create_node(token);
//             ft_nodeadd_back(new_lst, new_node);
//         }
//         if (current->content[i] == '|' || current->content[i] == '>'
//              || current->content == '<')
//         {
//             new_node = create_node(current->content);
//             ft_nodeadd_back(new_lst, new_node);
//         }
//         current = current->next;
        
//     }
// }


// void get_command(t_data *node_lst, t_node *current)
// {
//     char        *tmp;
//     char        *joined;
//     t_command   *new_cmd;

//     joined = NULL;
//     tmp = NULL;
//     new_cmd = create_new_command();
//     if (!new_cmd)
//         return ;
//     while (current)
//     {
//         while (current && ft_strcmp(current->content, "|") != 0)
//         {
//             if (!new_cmd->full_cmd)
//             {
//                 new_cmd->full_cmd = ft_strdup(current->content);
//                 if (!new_cmd->full_cmd)
//                     return ;
//             }
//             else
//             {
//                 tmp = ft_strjoin(new_cmd->full_cmd, " ");
//                 if (!tmp)
//                     return;
//                 joined = ft_strjoin(tmp, current->content);
//                 if (!joined)
//                 {
//                     free (tmp);
//                     return ;
//                 }
//                 free(tmp);
//                 free(new_cmd->full_cmd);
//                 new_cmd->full_cmd = joined;
//             }
//             if (!new_cmd->full_cmd)
//                 return;
//             current = current->next;
//         }
//         add_command(node_lst, new_cmd);
//         if (current && ft_strcmp(current->content, "|") == 0)
//             current = current->next;
//         new_cmd = create_new_command();
//         if (!new_cmd)
//             return ;
//     }
//     free_list(node_lst->node);
//     // print_command(node_lst);
//     print_command_info(*(node_lst->commands));
//     // free_list_cmd(node_lst->commands);
// }

// TokenType get_token_type(const char *token)
// {
//     if (ft_strcmp(token, "|") == 0)
//         return (PIPE);
//     else if (ft_strcmp(token, "<") == 0)
//         return (REDIR_IN);
//     else if (ft_strcmp(token, ">") == 0)
//         return (REDIR_OUT);
//     else if (ft_strcmp(token, ">>") == 0)
//         return (APPEND);
//     else if (ft_strcmp(token, "<<") == 0)
//         return (HERE_DOC);
//     return (ARG);
// }

// static int my_setenv(t_data *data, const char *name, const char *value, int overwrite)
// {
//     char *env_var;
//     char *eq_pos;
//     int index;

//     if (validate_input_cd(name, value) == -1)
//         return (-1);

//     index = find_env_var(data, name, &env_var, &eq_pos);
//     if (index != -1 && !overwrite)
//         return (0); // No update if the variable exists and overwrite is not allowed

//     // Create the new variable and make sure it's allocated
//     char *new_var = create_new_var(name, value);
//     if (!new_var)
//         return (-1);

//     // Debugging to check what we are about to set
//     printf("Setting env var: %s=%s\n", name, value);
//     // printf("Inside minishell, getcwd: %s\n", getenv("OLDPWD"));
//     // Update or add the environment variable to envp
//     return update_envp(data, index, new_var);

// }

// static int my_setenv(t_data *data, const char *name, const char *value, int overwrite)
// {
//     char *env_var;
//     char *eq_pos;
//     int index;

//     if (validate_input_cd(name, value) == -1)
//         return (-1);

//     index = find_env_var(data, name, &env_var, &eq_pos);
//     if (index != -1 && !overwrite)
//         return (0);

//     char *new_var = create_new_var(name, value);
//     if (!new_var)
//         return (-1);

//     return (update_envp(data, index, new_var));
// }

