/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   payload.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:15:33 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/04 18:15:45 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chan.h"

static size_t	ft_strlen(const char *str)
{
	size_t	counter;

	counter = 0;
	if (!str)
		return (0);
	while (str[counter])
		counter++;
	return (counter);
}

t_text_part	*make_res_part(char *result)
{
	t_text_part	*node;

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

static char	**text_part_mapi(t_text_part *head)
{
	t_text_part	*node;
	int			node_count;
	char		**result;

	if (!head)
		return (NULL);
	node = head;
	node_count = 0;
	while (node && node->content)
	{
		node_count++;
		node = node -> next;
	}
	result = malloc(sizeof(char *) * (node_count + 1));
	if (!result)
		return (NULL);
	node_count = 0;
	while (head && head->content)
	{
		result[node_count++] = head->content;
		head = head->next;
	}
	result[node_count] = NULL;
	return (result);
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
	while (iter && iter->length != 0)
	{
		if (iter->content[iter->length - 1] == '\n')
			iter->content[iter->length - 1] = '\0';
		iter->next = make_res_part(get_next_line(chan->side[0]));
		if (!iter->next)
			break ;
		iter = iter->next;
	}
	payload = text_part_mapi(head);
	free_res_part(head);
	return (payload);
}
