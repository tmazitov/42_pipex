/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_queue_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:41:25 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/05 21:58:38 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_com_node	*get_last(t_com_queue *q)
{
	t_com_node	*iter;

	if (!q || !q->nodes)
		return (NULL);
	iter = q->nodes;
	while (iter->next)
		iter = iter->next;
	return (iter);
}

t_com_node	*get_first(t_com_queue *q)
{
	t_com_node	*iter;

	if (!q || !q->nodes)
		return (NULL);
	iter = q->nodes;
	while (iter->prev)
		iter = iter->prev;
	return (iter);
}

t_com_node	*add_node(t_com_queue *q, char *command_line, char *env_path)
{
	t_com_node	*node;
	t_com_node	*last;

	node = make_node(command_line, env_path);
	if (!node)
		return (NULL);
	last = get_last(q);
	node->prev = last;
	if (last)
		last->next = node;
	return (node);
}

t_com_node	*get_node(t_com_queue *q)
{
	t_com_node
		*first;

	if (!q || !q->nodes)
		return (NULL);
	first = q->first;
	if (first)
		q->first = first->next;
	else 
		q->first = get_first(q);
	return (first);
}

void	*free_queue(t_com_queue *q)
{
	t_com_node	*last;
	t_com_node	*iter;

	if (!q)
		return (NULL);
	last = get_last(q);
	iter = last;
	while (last)
	{
		iter = last->prev;
		free_node(last);
		last = iter;
	}
	free(q);
	return (NULL);
}


t_com_node	*get_node_by_pid(t_com_queue *q, pid_t pid)
{
	t_com_node	*command;

	if (!q || !q->nodes)
		return (NULL);
	command = get_first(q);
	while (command)
	{
		if (command->proc_id == pid)
			return (command);
		command = command->next;
	}
	return (NULL);
}