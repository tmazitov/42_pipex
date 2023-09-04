/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_queue_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:35:47 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/04 17:03:03 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_com_node	*make_node(char *command_line, char *env_path)
{
	t_com_node	*node;
	char		**command_parts;

	if (!command_line)
		return (NULL);
	node = malloc(sizeof(t_com_node));
	if (!node)
		return (NULL);
	command_parts = ft_split(command_line, ' ');
	if (!command_parts)
	{
		free_node(node);
		return (NULL);
	}
	node->command_name = command_parts[0];
	node->args = command_parts;
	node->next = NULL;
	node->prev = NULL;
	node->command_path = find_command_path(command_parts[0], env_path);
	return (node);
}

void	print_node(t_com_node *node)
{
	int counter;
	
	counter = 0;
	if (!node)
		return ;
	ft_printf("node: %p\n", node);
	ft_printf("\tcommand:\t%s\n", node->command_name);
	ft_printf("\tpath:\t\t%s\n", node->command_path);
	ft_printf("\targs:\n");
	while(node->args[counter])
		ft_printf("\t\t# %s\n", node->args[counter++]);
	ft_printf("\tnext:\t\t%p\n", node->next);
	ft_printf("\tprev:\t\t%p\n", node->prev);
}

void	*free_node(t_com_node *node)
{
	if (!node)
		return (NULL);
	if (node->args)
		free_split(node->args);
	node->next = NULL;
	node->prev = NULL;
	free(node);
	return (NULL);
}