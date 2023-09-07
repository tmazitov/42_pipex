/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:16:31 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/07 19:17:39 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_com_queue	*make_queue(char **command_lines, char *env_path, int com_count)
{
	t_com_queue		*queue;
	t_com_node		*iter;
	int				counter;

	if (!command_lines || com_count == 0)
		return (NULL);
	queue = malloc(sizeof(t_com_queue));
	if (!queue)
		return (NULL);
	counter = 0;
	queue->nodes = NULL;
	iter = queue->nodes;
	while (command_lines[counter] && counter < com_count)
	{
		iter = add_node(queue, command_lines[counter], env_path);
		if (!iter)
			return (free_queue(queue));
		queue->nodes = iter;
		counter++;
	}
	if (make_queue_relationship(queue))
		return (free_queue(queue));
	queue->first = get_first(queue);
	queue->chan_closed = 0;
	return (queue);
}

void	*free_queue(t_com_queue *q)
{
	t_com_node	*last;
	t_com_node	*iter;

	if (!q)
		return (NULL);
	if (!q->chan_closed)
		free_queue_chan(q);
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

int	make_queue_relationship(t_com_queue *queue)
{
	t_com_node		*command;
	t_log_chan		*chan;

	if (!queue)
		return (1);
	command = get_first(queue);
	while (command)
	{
		if (command->prev)
			command->in_chan = chan;
		chan = make_log_chan();
		if (!chan)
			return (1);
		if (command->next)
			command->out_chan = chan;
		command = command->next;
	}
	return (0);
}

int	add_input(t_com_queue *queue, char *input_path)
{
	t_com_node		*first;

	if (!queue || !queue->nodes)
		return (1);
	first = get_first(queue);
	first->in_chan = make_input(input_path);
	return (first->in_chan == NULL);
}

int	add_output(t_com_queue *queue, char *output_path)
{
	t_com_node		*last;

	if (!queue || !queue->nodes)
		return (1);
	last = get_last(queue);
	last->out_chan = make_output(output_path);
	return (last->out_chan == NULL);
}
