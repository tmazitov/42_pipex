/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:54:35 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/25 21:16:03 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "get_next_line.h"

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

size_t		ft_strlen(const char *str);
char		**text_part_mapi(t_text_part *head);
char		**darr_union(char **darr1, char **darr2);
char		**ft_split(char const *str, char ch);
char		*ft_strjoin(char const *str1, char const *str2);
void		*free_split(char **split_result);
char		*ft_substr(char const *str, unsigned int start, size_t len);
char    	*find_command_path(const char *program_name, char* env_path);

// QUEUE
t_com_queue	*make_queue(char **command_lines, char *env_path, int com_count);
t_com_node	*make_node(char *command_line, char *env_path);
t_com_node	*get_node(t_com_queue *q);
t_com_node	*add_node(t_com_queue *q, char *command_line, char *env_path);
t_com_node	*get_first(t_com_queue *q);
t_com_node	*get_last(t_com_queue *q);
void		free_queue(t_com_queue *q);
void		free_node(t_com_node *node);

// Logs
typedef	struct s_log_chan
{
	int		*side;
}		t_log_chan;

t_log_chan	*make_log_chan();
void		*free_log_chan(t_log_chan *chan);
char		**get_chan_payload(t_log_chan *chan);


// MULTIPROCCESSING
t_log_chan	*exec_command(t_com_node *command, t_log_chan *old_chan);

// TEST
void test_log(t_log_chan *chan);
#endif