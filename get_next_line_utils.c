/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:05:30 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/12 13:43:21 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *str, int ch)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == ch)
			return (str);
		str++;
	}
	if (*str == ch)
		return (str);
	return (NULL);
}

int	calc_next_line_length(t_text_part *line_start)
{
	int			length;
	int			counter;
	t_text_part	*part;
	char		*content_start;

	length = 0;
	part = line_start;
	while (part && part->content)
	{
		counter = 0;
		content_start = get_content_start(line_start, part);
		while (content_start[counter] && content_start[counter] != '\n')
			counter++;
		length += counter;
		part = part->next;
	}
	if (content_start[counter] == '\n')
		length++;
	return (length);
}

char	*feed_next_line(int result_len, t_text_part *line_start)
{
	char		*result;
	char		*content_start;
	t_text_part	*part;

	result = malloc(sizeof(char) * (result_len + 1));
	if (!result)
		return (NULL);
	part = line_start;
	result_len = 0;
	while (part)
	{
		content_start = get_content_start(line_start, part);
		while (*content_start && *content_start != '\n')
			result[result_len++] = *content_start++;
		part = part->next;
	}
	if (*content_start == '\n')
		result[result_len++] = '\n';
	result[result_len] = '\0';
	return (result);
}

char	*get_content_start(t_text_part *line_start, t_text_part *part)
{
	if (!line_start || !part)
		return (NULL);
	if (part == line_start && part->rem <= BUFFER_SIZE)
		return (part->content + part->rem);
	else
		return (part->content);
}

void	*free_root(t_text_part	*part, int save_last)
{
	if (!part)
		return (NULL);
	if (part->next)
		free_root(part->next, save_last);
	else if (save_last)
		return (NULL);
	if (part->content)
		free(part->content);
	free(part);
	return (NULL);
}
