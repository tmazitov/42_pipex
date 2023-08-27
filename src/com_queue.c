/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:16:31 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/26 21:12:26 by tmazitov         ###   ########.fr       */
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
	queue->nodes = NULL;
	counter = 0;
	iter = queue->nodes;
	while(command_lines[counter] && counter < com_count)
	{
		iter = add_node(queue, command_lines[counter++], env_path);
		if (!iter)
		{
			free_queue(queue);
			return (NULL);
		}
		queue->nodes = iter;
	} 
	return (queue);
}

