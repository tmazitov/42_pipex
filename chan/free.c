/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:05:56 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/26 22:29:44 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chan.h"

void	*free_log_chan(t_log_chan *chan)
{
	if (!chan)
		return (NULL);
	close_write(chan);
	close_read(chan);
	if (chan->side)
		free(chan->side);
	free(chan);
	return (NULL);
}