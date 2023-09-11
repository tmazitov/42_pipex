/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:43:52 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/11 13:26:34 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

static int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	size_t	counter;
	int		result;

	counter = 0;
	result = 0;
	while ((str1[counter] || str2[counter]) && counter < num)
	{
		if (str1[counter] != str2[counter])
		{
			result = (unsigned char)str1[counter]
				- (unsigned char)str2[counter];
			return (result);
		}
		counter++;
	}
	if (num != counter)
		result = (unsigned char)str1[counter] - (unsigned char)str2[counter];
	return (result);
}

int	check_heredoc(char *input_path)
{
	return (ft_strncmp(input_path, "here_doc", ft_strlen(input_path)) == 0);
}

static int	fill_heredoc(t_log_chan *chan, char	*limiter)
{
	char	*buffer;

	buffer = NULL;
	while (!buffer || ft_strncmp(buffer, limiter, ft_strlen(buffer) - 1))
	{
		if (buffer)
			write(chan->side[1], buffer, ft_strlen(buffer));
		ft_printf("pipe heredoc> ");
		buffer = get_next_line(STDIN_FILENO);
		if (!buffer)
			return (1);
	}
	close_write(chan);
	return (0);
}

int	add_heredoc(t_com_queue *q, char *limiter)
{
	t_log_chan	*heredoc;
	t_com_node	*first;

	if (!q || !q->nodes)
		return (1);
	heredoc = make_log_chan();
	if (!heredoc)
		return (1);
	first = get_first(q);
	first->in_chan = heredoc;
	fill_heredoc(heredoc, limiter);
	return (first->in_chan == NULL);
}
