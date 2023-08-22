/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:54:35 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/22 21:37:28 by tmazitov         ###   ########.fr       */
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
typedef	struct s_log_session
{
	int		fd;
	char	*path;
	char	**result;
}		t_log_session;

t_log_session	*make_log_session(t_com_node *node);
char			**fill_log_session(char *log_path);

// MULTIPROCCESSING
t_log_session	*exec_node(t_com_node *node, t_log_session	*old_log_session);
#endif