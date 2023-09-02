/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:49:36 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/02 22:32:00 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int write_output(int output_fd, t_log_chan *chan)
{
	char	**chan_payload;
	int		counter;

	chan_payload = get_chan_payload(chan);
	if (!chan_payload)
		return (1);
	counter = 0;
	while (chan_payload[counter])
	{
		write(output_fd, chan_payload[counter], ft_strlen(chan_payload[counter]));
		write(output_fd, "\n", 1);		
		counter++;
	}
	free_split(chan_payload);
	return (0);
}

int	make_output(char *output_path, t_log_chan *output_chan)
{
	int	output_fd;
	int output_result;
	
	output_fd = open(output_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (output_fd < 0)
		return (1);
	if (output_chan->status)
	{
		close(output_fd);
		return (output_chan->status);
	}
	output_result = write_output(output_fd, output_chan);
	close(output_fd);
	return (output_result);
}


int	check_output(char *output_path)
{
	return access(output_path, W_OK);
}