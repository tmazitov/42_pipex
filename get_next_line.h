/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:05:35 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/08 18:43:44 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_text_part
{
	char				*content;
	int					length;
	int					rem;
	struct s_text_part	*next;
}		t_text_part;

char			*get_next_line(int fd);
t_text_part		*ft_make_text_part(int fd);
char			*ft_strchr(char *str, int ch);
char			*ft_parts_to_text(t_text_part	*part);
void			*free_root(t_text_part *part, int save_last);
char			*get_content_start(t_text_part *line_start, t_text_part *part);
t_text_part		*find_new_remainder(t_text_part *root, t_text_part *p);
char			*feed_next_line(int result_len, t_text_part *line_start);
int				calc_next_line_length(t_text_part *line_start);
#endif