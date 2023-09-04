/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:02:20 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/04 18:14:24 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../get_next_line/get_next_line.h"

typedef struct s_log_chan
{
	int	*side;
	int	status;
}		t_log_chan;

t_log_chan	*make_log_chan(void);
void		*free_log_chan(t_log_chan *chan);
char		**get_chan_payload(t_log_chan *chan);
int			close_write(t_log_chan *chan);
int			close_read(t_log_chan *chan);
int			set_write(t_log_chan *chan, int fd);
int			set_read(t_log_chan *chan, int fd);

#endif // !CHAN_H
