/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:54:35 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/11 10:46:03 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
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
# include "../printf/ft_printf.h"

typedef struct s_com_node
{
	char				*name;
	char				*path;
	char				**args;
	struct s_com_node	*next;
	struct s_com_node	*prev;
	t_log_chan			*in_chan;
	t_log_chan			*out_chan;
	int					proc_id;
	int					proc_status;
}		t_com_node;

typedef struct s_com_queue
{
	t_com_node	*nodes;
	t_com_node	*first;
	int			chan_closed;
}		t_com_queue;

// QUEUE NODE
t_com_node	*make_node(char *command_line, char *env_path);
void		*free_node(t_com_node *node);

// QUEUE
int			make_queue_relationship(t_com_queue *queue);
t_com_queue	*make_queue(char **command_lines, char *env_path, int com_count);
t_com_node	*get_node(t_com_queue *queue);
t_com_node	*add_node(t_com_queue *queue, char *command_line, char *env_path);
t_com_node	*get_first(t_com_queue *queue);
t_com_node	*get_last(t_com_queue *queue);
void		*free_queue(t_com_queue *queue);
void		*free_queue_relationship(t_com_queue *queue);
t_com_node	*get_node_by_pid(t_com_queue *queue, pid_t pid);

// MULTIPROCCESSING
void		run_command_proc(t_com_node *command, char **envp, t_com_queue *q);

// INPUT FILE
int			add_input(t_com_queue *queue, char *input_path);
int			check_input(char *input_path);
t_log_chan	*make_input(char *input_path);

// OUTPUT FILE
int			add_output(t_com_queue *queue, char *output_path);
t_log_chan	*make_output(char *output_path);
#endif
