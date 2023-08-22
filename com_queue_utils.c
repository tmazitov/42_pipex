/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_queue_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:41:25 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/22 17:58:34 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_com_node	*get_last(t_com_queue *q)
{
	t_com_node	*iter;

	if (!q || !q->nodes)
		return (NULL);
	iter = q->nodes;
	while(iter->next)
		iter = iter->next;
	return (iter);
}

t_com_node	*get_first(t_com_queue *q)
{
	t_com_node	*iter;

	if (!q || !q->nodes)
		return (NULL);
	iter = q->nodes;
	while(iter->prev)
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
	t_com_node	*first;
	
	if (!q || !q->nodes)
		return (NULL);
	first = get_first(q);
	if (first->next)
		first->next->prev = NULL;
	else
		q->nodes = NULL;
	first->next = NULL;
	return (first);
}

void	free_queue(t_com_queue *q)
{
	t_com_node	*last;
	if (!q)
		return ;
	last = get_last(q);
	while (last)
	{
		free(last->command_name);
		free(last->command_path);
		free(last->args);
		if (last->prev)
		{
			last = last->prev;
			last->next->next = NULL;
			last->next->prev = NULL;
			free(last->next);
			last->next = NULL;
		}
		else
		{
			last->next = NULL;
			last->prev = NULL;
			free(last->next);
		}
	}
}