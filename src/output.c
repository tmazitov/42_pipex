/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:49:36 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/05 19:33:18 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// static int	write_output(int output_fd, t_log_chan *chan)
// {
// 	char	**chan_payload;
// 	int		ctn;

// 	chan_payload = get_chan_payload(chan);
// 	if (!chan_payload)
// 		return (1);
// 	ctn = 0;
// 	while (chan_payload[ctn])
// 	{
// 		write(output_fd, chan_payload[ctn], ft_strlen(chan_payload[ctn]));
// 		write(output_fd, "\n", 1);
// 		ctn++;
// 	}
// 	free_split(chan_payload);
// 	return (0);
// }

static t_log_chan	*setup_output_chan(int output_fd)
{
	t_log_chan	*log_chan;

	log_chan = make_log_chan();
	if (!log_chan)
		return (free_log_chan(log_chan));
	close_write(log_chan);
	close_read(log_chan);
	set_write(log_chan, output_fd);
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

int	check_output(char *output_path)
{
	return (access(output_path, W_OK));
}
