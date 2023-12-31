/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:49:28 by tmazitov          #+#    #+#             */
/*   Updated: 
2023/09/05 14:01:34 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_log_chan	*setup_input_chan(int input_fd)
{
	t_log_chan	*log_chan;

	log_chan = make_log_chan();
	if (!log_chan)
		return (free_log_chan(log_chan));
	close_read(log_chan); 
	close_write(log_chan);
	set_read(log_chan, input_fd);
	set_write(log_chan, -1);
	return (log_chan);
}

t_log_chan	*make_input(char *input_path)
{
	int			input_fd;
	t_log_chan	*log_chan;

	input_fd = open(input_path, O_RDONLY);
	if (input_fd < 0)
		return (NULL);
	log_chan = setup_input_chan(input_fd);
	if (!log_chan)
	{
		close(input_fd);
		return (NULL);
	}
	return (log_chan);
}

int	check_input(char *input_path)
{
	return (access(input_path, R_OK));
}
