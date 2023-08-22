/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:05:33 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/11 15:36:03 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_text_part	*ft_make_text_part(int fd)
{
	t_text_part	*part;

	part = malloc(sizeof(t_text_part));
	if (!part)
		return (NULL);
	part->next = NULL;
	part->content = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!part->content)
	{
		free(part);
		return (NULL);
	}
	part->length = read(fd, part->content, BUFFER_SIZE);
	if (part->length == 0 || part->length == -1)
	{
		free(part->content);
		free(part);
		return (NULL);
	}
	part->content[part->length] = '\0';
	part->rem = 0;
	return (part);
}

char	*ft_parts_to_text(t_text_part	*line_start)
{
	int			result_len;

	if (!line_start)
		return (NULL);
	result_len = calc_next_line_length(line_start);
	if (result_len == 0)
		return (NULL);
	return (feed_next_line(result_len, line_start));
}

t_text_part	*find_new_remainder(t_text_part *root, t_text_part *p)
{
	int	is_next_line;

	is_next_line = ft_strchr(p->content + p->rem, '\n') != NULL;
	free_root(root, is_next_line);
	if (is_next_line)
	{
		p->rem = ft_strchr(p->content + p->rem, '\n') - p->content + 1;
		if (p->rem == BUFFER_SIZE)
			return (free_root(p, 0));
		else
			return (p);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_text_part	*root;
	t_text_part			*p;
	char				*result;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT32_MAX)
		return (NULL);
	if (!root)
		root = ft_make_text_part(fd);
	if (!root)
		return (NULL);
	p = root;
	while (p && ft_strchr(p->content + p->rem, '\n') == NULL)
	{
		p->next = ft_make_text_part(fd);
		if (!p->next)
			break ;
		p = p->next;
		if (p->length != BUFFER_SIZE 
			|| (p->content && ft_strchr(p->content, '\n')))
			break ;
	}
	result = ft_parts_to_text(root);
	root = find_new_remainder(root, p);
	return (result);
}
