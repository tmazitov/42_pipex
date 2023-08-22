/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:44:34 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/22 21:51:12 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_log_session	*exec_node(t_com_node *node, t_log_session	*old_log_session)
{
	pid_t			fork_pid;
	int				fork_status;
	int				default_fd;
	t_log_session	*log_file;
	char			**input_data;

	if (!node)
		return (NULL);
	log_file = make_log_session(node);
	printf("log file created : %d\n", log_file->fd);
	if (!log_file)
		return (NULL);
	default_fd = dup(STDOUT_FILENO);
	dup2(log_file->fd, STDOUT_FILENO);
	fork_pid = fork();
	if (fork_pid == -1)
	{
		perror("fork create error");
		exit(EXIT_FAILURE);
	}
	
	if (fork_pid != 0)
	{
		waitpid(fork_pid, &fork_status, 0);
		dup2(default_fd, STDOUT_FILENO);
		close(log_file->fd);
		log_file->result = fill_log_session(log_file->path);
		unlink(log_file->path);
		printf("log file is filled!\n");
		return (log_file);
	}

	if (old_log_session)
	{
		input_data = darr_union(node->args, old_log_session->result);
		execve(node->command_path, input_data, NULL);
	}
	else
		execve(node->command_path, node->args, NULL);
	exit(EXIT_SUCCESS);
}