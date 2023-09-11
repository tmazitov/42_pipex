/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:49:36 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/11 10:38:01 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

t_log_chan	*make_output(char *output_path)
{
	int			output_fd;
	t_log_chan	*log_chan;

	output_fd = open(output_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
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
