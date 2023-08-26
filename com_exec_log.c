/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exec_log.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:29:01 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/26 15:29:54 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"

t_log_chan	*make_log_chan()
{
	t_log_chan	*chan;
	int			pipe_result;

	chan = malloc(sizeof(t_log_chan));
	if (!chan)
		return (NULL);
	chan->side = malloc(sizeof(int) * (2));
	if (!chan)
		return (free_log_chan(chan));
	pipe_result = pipe(chan->side);
	if (pipe_result == -1)
	{
		printf("failed pipe\n");
		free(chan);
		return (NULL);
	}
	return (chan);
}

void	*free_log_chan(t_log_chan *chan)
{
	if (chan->side)
		free(chan->side);
	free(chan);
	return (NULL);
}

t_text_part		*make_res_part(char *result)
{	
	t_text_part		*node;
	
	if (!result)
		return (NULL);
	node = malloc(sizeof(t_text_part));
	if (!node)
	{
		free(result);
		return (NULL);
	}
	node->next = NULL;
	node->rem = 0;
	node->length = ft_strlen(result);
	node->content = result;
	return (node);
}

void	*free_res_part(t_text_part *node)
{
	if (!node)
		return (NULL);
	if (node->next)
		free_res_part(node->next);
	node->content = NULL;
	free(node);
	return (NULL);
}

char	**get_chan_payload(t_log_chan *chan)
{
	char			*head_line;
	t_text_part		*head;
	t_text_part		*iter;
	char			**payload;

	if (!chan)
		return (NULL);
	head_line = get_next_line(chan->side[0]);
	head = make_res_part(head_line);
	if (!head)
		return (NULL);

	iter = head;
	while (iter && ft_strlen(iter->content) != 0)
	{
		if (iter->content[ft_strlen(iter->content) - 1] == '\n')
			iter->content[ft_strlen(iter->content) - 1] = '\0';
		iter->next = make_res_part(get_next_line(chan->side[0]));
		if (!iter->next)
			break;
		iter = iter->next;
	}
	payload = text_part_mapi(head);
	int counter = 0;
	free_res_part(head);
	return (payload);
}