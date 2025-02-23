/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luji <luji@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:49:39 by rsham             #+#    #+#             */
/*   Updated: 2025/02/23 15:43:25 by luji             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// handle pipe process
// if (|) -> create a pipe
// pipe_fd[0]: Read end → Connects to the next command’s infile.
// pipe_fd[1]: Write end → Connects to the current command’s outfile.
// assign fds
// set outfile -> pipe_fd[1]
// set infile -> pipe_fd[0]

#include <stdio.h>

// Create and initialize a new command node
t_command *create_new_command()
{
    t_command *new_cmd = malloc(sizeof(t_command));
    if (!new_cmd)
        return NULL;

    // new_cmd->infile = infile;
    // new_cmd->outfile = outfile;
    new_cmd->full_cmd = NULL;
    new_cmd->full_path = NULL;
    new_cmd->next = NULL;
    return new_cmd;
}
//initialize in/out files
// void    init_io_file(int infile, int outfile)
// {
//     infile = STDIN_FILENO;
//     outfile = STDOUT_FILENO;
// }

// to print the new commands
// To print the new commands
void print_command(t_command *newcmd)
{
    int i = 0;
    while (newcmd)
    {
        ft_printf("%d ", i);
        ft_printf("command is %s\n", newcmd->full_cmd);
        newcmd = newcmd->next;  // Move to next command in the linked list
        i++;
    }
}


void get_command(t_data *node_lst, t_node *current)
{
  //current == tokens ..... new_cmd == new linked list after split and add
	t_command *new_cmd;
	
	new_cmd = create_new_command();
    while (current)
    {
		while (current && ft_strcmp(current->content, "|" ) != '0')
        {
			// write(1, "h\n", 2);
			if (!new_cmd->full_cmd)
			{
            	new_cmd->full_cmd = ft_strdup(current->content);
				ft_printf("new_cmd  = %s\n", new_cmd->full_cmd);
			}
			else
			new_cmd->full_cmd = ft_strjoin(new_cmd->full_cmd, current->content);
			if (!new_cmd->full_cmd)
				return;
			ft_printf("after join new_cmd  = %s\n", new_cmd->full_cmd);
			// add_command(node_lst, new_cmd);
			current = current->next;
        }
		add_command(node_lst, new_cmd);
		if (current && ft_strcmp(current->content, "|") == 0)
			current = current->next;
		new_cmd = create_new_command();
		// new_cmd = new_cmd->next;
    }
	print_command(node_lst->commands);
}

//add new node to the linked list
void add_command(t_data *data, t_command *new_cmd)
{
    t_command *tmp;

    if (!data->commands)
        data->commands = new_cmd;
    else
    {
        tmp = data->commands;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_cmd;
    }
}

// t_command *get_commands(t_node *tokens)
// {
//     t_command *cmds = NULL;
//     t_command *current_cmd = NULL;
//     int infile = STDIN_FILENO;
//     int outfile = STDOUT_FILENO;

//     while (tokens)
//     {
//         // Handle redirections
//         handle_redirections(tokens, &infile, &outfile);

//         // Create a new command node if it's the first one or after a pipe
//         if (!current_cmd || tokens->type == PIPE)
//         {
//             if (tokens->type == PIPE)
//                 tokens = tokens->next; // Move to next token after '|'

//             current_cmd = malloc(sizeof(t_command));
//             if (!current_cmd)
//                 return (NULL); // Handle malloc failure
//             current_cmd->infile = infile;
//             current_cmd->outfile = outfile;
//             current_cmd->full_cmd = NULL; // Initialize empty command list
//             current_cmd->full_path = NULL; // Will resolve later
//             current_cmd->next = NULL;

//             // Add the command to the list
//             if (!cmds)
//                 cmds = current_cmd;
//             else
//             {
//                 t_command *tmp = cmds;
//                 while (tmp->next)
//                     tmp = tmp->next;
//                 tmp->next = current_cmd;
//             }
//         }

//         // Collect command arguments
//         if (tokens && tokens->type == ARG)
//             add_argument(&(current_cmd->full_cmd), tokens->content);

//         tokens = tokens->next;
//     }

//     return cmds;
// }

