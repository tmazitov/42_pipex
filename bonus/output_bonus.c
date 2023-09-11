/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:21:08 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/11 13:52:49 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_bonus.h"

static t_log_chan	*setup_output_chan(int output_fd)
{
	t_log_chan	*log_chan;

	log_chan = make_log_chan();
	if (!log_chan)
		return (free_log_chan(log_chan));
	close_write(log_chan);
	close_read(log_chan);
	set_write(log_chan, output_fd);
	set_read(log_chan, -1);
	return (log_chan);
}

static t_log_chan	*make_output_heredoc(char *output_path, int is_heredoc)
{
	int			output_fd;
	t_log_chan	*log_chan;

	if (!is_heredoc)
		output_fd = open(output_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		output_fd = open(output_path, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (output_fd < 0)
		return (NULL);
	log_chan = setup_output_chan(output_fd);
	if (!log_chan)
	{
		close(output_fd);
		return (NULL);
	}
	return (log_chan);
}

int	add_output_heredoc(t_com_queue *queue, char *output_path, int is_heredoc)
{
	t_com_node		*last;

	if (!queue || !queue->nodes)
		return (1);
	last = get_last(queue);
	last->out_chan = make_output_heredoc(output_path, is_heredoc);
	return (last->out_chan == NULL);
}
