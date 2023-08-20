/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 17:54:35 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/20 23:10:58 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"

#ifndef PIPEX_H


typedef	struct s_com_node
{
	char				*command_name;
	char				*command_path;
	char				**args;
	struct s_com_node	*next;
}		t_com_node;

char		**ft_split(char const *str, char ch);
char	*ft_strjoin(char const *str1, char const *str2);
t_com_node 	*make_list(char **command_lines, char *env_path);
t_com_node	*make_node(char *command_line, char *env_path);
void		*free_list(t_com_node	*node);
char		*ft_substr(char const *str, unsigned int start, size_t len);
char    	*find_command_path(const char *program_name, char* env_path);

#endif
