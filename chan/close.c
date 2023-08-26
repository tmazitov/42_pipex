/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:03:09 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/26 22:41:15 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chan.h"

int	close_read(t_log_chan *chan)
{
	return close(chan->side[0]);
}

int close_write(t_log_chan *chan)
{
	return close(chan->side[1]);
}