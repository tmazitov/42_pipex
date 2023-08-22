/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exec_log.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:29:01 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/22 21:38:33 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"

char	*make_log_file_path(t_com_node *node)
{
	char	*full_filename;
	char	*path;

	if (!node)
		return (NULL);
	full_filename = ft_strjoin(node->command_name, ".txt");
	path = ft_strjoin("./temp-", full_filename);
	free(full_filename);
	return (path);
}

t_log_session	*make_log_session(t_com_node *node)
{
	t_log_session	*log_session;

	if (!node)
		return (NULL);
	log_session = malloc(sizeof(t_log_session));
	if (!log_session)
		return (NULL);
	log_session->path = make_log_file_path(node);
	log_session->fd = open(log_session->path, O_WRONLY | O_RDONLY | O_APPEND | O_CREAT, 0644);
	log_session->result = NULL;
	return (log_session);
}

t_text_part		*make_res_part(char *result)
{	
	t_text_part		*node;
	
	if (!result)
		return (NULL);
	node = malloc(sizeof(t_text_part));
	if (!node)
		return (NULL);
	node->content = result;
	return (node);
}

char	**fill_log_session(char *log_path)
{
	int				fd;
	char			*next_line;
	t_text_part		*head;
	t_text_part		*iter;

	if (!log_path)
		return (NULL);
	fd = open(log_path, O_RDONLY);
	if (!fd)
	{
		close(fd);
		return (NULL);		
	}
	next_line = get_next_line(fd);
	if (!next_line)
	{
		close(fd);
		return (NULL);		
	}
	head = make_res_part(next_line);
	if (!head)
	{
		free(next_line);
		return (NULL);
	}
	iter = head;
	while (iter)
	{
		iter->content[ft_strlen(iter->content) - 1] = '\0';
		iter->next = make_res_part(get_next_line(fd));
		iter = iter->next;
	}
	close(fd);
	return text_part_mapi(head);
}