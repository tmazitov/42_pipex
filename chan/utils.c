/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:17:46 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/26 22:53:21 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chan.h"

size_t	ft_strlen(const char *str)
{
	size_t	counter;

	counter = 0;
	if (!str)
		return (0);
	while (str[counter])
		counter++;
	return (counter);
}

char	**text_part_mapi(t_text_part *head)
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