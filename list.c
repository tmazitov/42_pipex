/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:59:42 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/20 23:07:24 by tmazitov         ###   ########.fr       */
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
	if (!command_parts || !command_parts[0])
	{
		free(node);
		return (NULL);
	}
	node->command_name = command_parts[0];
	node->command_path = find_command_path(command_parts[0], env_path);
	node->args = command_parts + 1;
	node->next = NULL;
	return (node);
}

void	*free_list(t_com_node	*node)
{
	if (!node)
		return (NULL);
	if(node->next)
		free_list(node->next);
	free(node->command_name);
	free(node->command_path);
	free(node->args);
	free(node);
	return (NULL);
}

t_com_node *make_list(char **command_lines, char *env_path, int com_count)
{
	t_com_node	*head;
	t_com_node	*iter;
	int		counter;

	if (!command_lines || com_count == 0)
		return (NULL);
	counter = 0;
	head = make_node(command_lines[counter++], env_path);
	if (!head)
		return (NULL);
	iter = head; 
	while(command_lines[counter] && counter < com_count)
	{
		printf("comm: %s\n", command_lines[counter]);
		iter->next = make_node(command_lines[counter], env_path);
		if (!iter->next)
			return free_list(head);
		iter = iter->next;
		counter++;
	}
	return (head);
}
