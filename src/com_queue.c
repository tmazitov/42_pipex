/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:16:31 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/01 19:46:12 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	command_not_found(t_com_queue *q, t_com_node *last, int is_not_first)
{
	ft_printf("command not found: %s\n", last->command_name);
	free_queue(q);
	if (is_not_first)
		panic(NULL, 127);
	else 
		panic(NULL, 1);
}

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
	queue->nodes = NULL;
	counter = 0;
	iter = queue->nodes;
	while(command_lines[counter] && counter < com_count)
	{
		iter = add_node(queue, command_lines[counter], env_path);
		if (!iter)
		{
			free_queue(queue);
			if (counter)
				panic("create another command error", 1);
			else	
				panic("create first command error", 0);
		}
		if (iter && !iter->command_path)
			command_not_found(queue, iter, counter);
		queue->nodes = iter;
		counter++;
	} 
	return (queue);
}

