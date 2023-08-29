/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:49:36 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/29 20:53:43 by tmazitov         ###   ########.fr       */
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
	free(chan_payload);
	return (0);
}

int	make_output(char *output_path, t_log_chan *output_chan)
{
	int	output_fd;
	int output_result;
	
	output_fd = open(output_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (output_fd == -1)
		return (1);
	output_result = write_output(output_fd, output_chan);
	close(output_fd);
	free_log_chan(output_chan);
	return (output_result);
}


int	check_output(char *output_path)
{
	return access(output_path, W_OK);
}