/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_queue_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:35:47 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/28 21:50:48 by tmazitov         ###   ########.fr       */
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
	node->command_path = find_command_path(command_parts[0], env_path);
	if (!node->command_path)
	{
		free_node(node);
		perror("command not found");
		exit(EXIT_FAILURE);
	}
	node->next = NULL;
	return (node);
}

void	*free_node(t_com_node *node)
{
	if (!node)
		return (NULL);
	free(node->command_name);
	free(node->command_path);
	free(node->args);
	node->next = NULL;
	node->prev = NULL;
	return (NULL);
}