/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:54:35 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/29 13:08:48 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../chan/chan.h"
# include "../utils/utils.h"
# include "../get_next_line/get_next_line.h"

#ifndef PIPEX_H

typedef	struct s_com_node
{
	char				*command_name;
	char				*command_path;
	char				**args;
	struct s_com_node	*next;
	struct s_com_node	*prev;
}		t_com_node;

typedef	struct s_com_queue
{
	t_com_node	*nodes;
}		t_com_queue;

// QUEUE
t_com_queue	*make_queue(char **command_lines, char *env_path, int com_count);
t_com_node	*make_node(char *command_line, char *env_path);
t_com_node	*get_node(t_com_queue *q);
t_com_node	*add_node(t_com_queue *q, char *command_line, char *env_path);
t_com_node	*get_first(t_com_queue *q);
t_com_node	*get_last(t_com_queue *q);
void		free_queue(t_com_queue *q);
void		*free_node(t_com_node *node);

// MULTIPROCCESSING
t_log_chan	*exec_node(t_com_node *command, t_log_chan *old_chan);

// INPUT FILE
int			check_input(char *input_path);
t_log_chan	*make_input(char *input_path);

// OUTPUT FILE
int			check_output(char *output_path);
int			make_output(char *output_path, t_log_chan *chan);
#endif
