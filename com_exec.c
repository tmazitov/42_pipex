/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:44:34 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/26 15:28:53 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void test_log(t_log_chan *chan)
{
	int	log_fd = open("./test.txt", O_WRONLY | O_CREAT , 0644);
	char *buffer = malloc(sizeof(char) * 100 + 1);
	int read_result = read(chan->side[0], buffer, 100);
	buffer[100] = '\0';
	write(log_fd, buffer, 100);
	write(log_fd, "\n", 1);
	close(log_fd);
}

int	exec_node(t_com_node *command, t_log_chan *new_chan, t_log_chan *old_chan)
{
	pid_t			fork_pid;
	int				fork_status;
	char			**input_data;
	char			**payload;

	if (!command || !old_chan || !new_chan)
		return (EXIT_FAILURE);

	fork_pid = fork();
	if (fork_pid == -1)
	{
		perror("fork create error");
		exit(EXIT_FAILURE);
	}
	if (fork_pid != 0)
	{
		waitpid(fork_pid, &fork_status, 0);
		close(old_chan->side[0]);
		return (EXIT_SUCCESS);
	}
	if (fork_pid == 0)
	{
		close(new_chan->side[0]);
		payload = get_chan_payload(old_chan);
		close(old_chan->side[0]);
		input_data = darr_union(command->args, payload);
		execve(command->command_path, input_data, NULL);
		exit(EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

t_log_chan		*exec_command(t_com_node *command, t_log_chan *old_chan)
{
	int			default_fd;
	t_log_chan	*new_chan;
	char		*payload;
	
	new_chan = make_log_chan();
	if (!new_chan)
		return (free_log_chan(new_chan));
	default_fd = dup(STDOUT_FILENO);
	if (dup2(new_chan->side[1], STDOUT_FILENO) == -1)
		return (free_log_chan(new_chan));
	close(new_chan->side[1]);
	if (exec_node(command, new_chan, old_chan) != EXIT_SUCCESS)
		return (free_log_chan(new_chan));
	if (dup2(default_fd, STDOUT_FILENO) == -1)
		return (free_log_chan(new_chan));
	close(default_fd);
	free_log_chan(old_chan);
	return (new_chan);
}