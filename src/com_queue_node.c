/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_queue_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:35:47 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/07 19:31:34 by tmazitov         ###   ########.fr       */
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
	node->name = command_parts[0];
	node->args = command_parts;
	node->next = NULL;
	node->prev = NULL;
	node->path = find_command_path(command_parts[0], env_path);
	node->in_chan = NULL;
	node->out_chan = NULL;
	node->proc_id = -1;
	node->proc_status = 0;
	return (node);
}

void	set_in_chan(t_com_node *node, t_log_chan *chan)
{
	node->in_chan = chan;
}

void	set_out_chan(t_com_node *node, t_log_chan *chan)
{
	node->out_chan = chan;
}

t_com_node	*get_node_by_pid(t_com_queue *q, pid_t pid)
{
	t_com_node	*command;

	command = get_first(q);
	while (command)
	{
		if (command->proc_id == pid)
			return (command);
		command = command->next;
	}
	return (NULL);
}

void	*free_node(t_com_node *node)
{
	if (!node)
		return (NULL);
	if (!ft_strchr(node->name, '/') && node->path)
		free(node->path);
	if (node->args)
		free_split(node->args);
	node->next = NULL;
	node->prev = NULL;
	free(node);
	return (NULL);
}
