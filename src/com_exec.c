/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:44:34 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/27 20:08:41 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void test_log(t_log_chan *chan)
// {
// 	int	log_fd = open("./test.txt", O_WRONLY | O_APPEND , 0644);
// 	char *buffer = malloc(sizeof(char) * 100 + 1);
// 	int read_result = read(chan->side[0], buffer, 100);
// 	buffer[100] = '\0';
// 	write(log_fd, buffer, 100);
// 	write(log_fd, "=======\n", 8);
// 	close(log_fd);
// }

int	exec_node(t_com_node *command, t_log_chan *new_chan, t_log_chan *old_chan)
{
	pid_t			fork_pid;
	int				fork_status;

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
		// test_log(new_chan);
		return (fork_status);
	}
	if (fork_pid == 0)
	{
		// Read input
		dup2(old_chan->side[0], STDIN_FILENO);
		close_read(old_chan);

		// Write output
		dup2(new_chan->side[1], STDOUT_FILENO);
		close_write(new_chan);

		execve(command->command_path, command->args, NULL);
	}
	return (EXIT_FAILURE);
}

t_log_chan		*exec_command(t_com_node *command, t_log_chan *old_chan)
{
	t_log_chan	*new_chan;
	
	new_chan = make_log_chan();
	if (!new_chan)
		return (free_log_chan(new_chan));
	printf("exec: %d\n", exec_node(command, new_chan, old_chan));
	close_write(new_chan);
	free_log_chan(old_chan);
	return (new_chan);
}