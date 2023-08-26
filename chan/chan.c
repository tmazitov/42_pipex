/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:02:05 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/26 22:44:59 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chan.h"

t_log_chan	*make_log_chan()
{
	t_log_chan	*chan;
	int			pipe_result;

	chan = malloc(sizeof(t_log_chan));
	if (!chan)
		return (NULL);
	chan->side = malloc(sizeof(int) * (2));
	if (!chan->side)
		return (free_log_chan(chan));
	pipe_result = pipe(chan->side);
	if (pipe_result == -1)
	{
		free(chan->side);
		free(chan);
		return (NULL);
	}
	return (chan);
}

int	set_write(t_log_chan *chan, int fd)
{
	if (!chan || !chan->side)
		return (-1);
	chan->side[1] = fd;
	return (0);
}

int set_read(t_log_chan *chan, int fd)
{
	if (!chan || !chan->side)
		return (-1);
	chan->side[0] = fd;
	return (0);
}