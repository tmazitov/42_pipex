/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:44:34 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/29 13:34:58 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void exec_command(t_com_node *command, t_log_chan *new_chan, t_log_chan *old_chan)
{
	// Read input
	if (dup2(old_chan->side[0], STDIN_FILENO) == -1)
	{
		perror("dup2 error : create dub for STDIN_FILENO was failed");
		exit(EXIT_FAILURE);
	}
	if (close_read(old_chan) == -1)
	{
		perror("chan close error : close of the read fd was failed");
		exit(EXIT_FAILURE);
	}

	// Write output
	if (dup2(new_chan->side[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 error : create dub for STDOUT_FILENO was failed");
		exit(EXIT_FAILURE);
	}
	if (close_write(new_chan) == -1)
	{
		perror("chan close error : close of the write fd was failed");
		exit(EXIT_FAILURE);
	}
	if (execve(command->command_path, command->args, NULL) == -1)
	{
		perror("execve error");
		exit(EXIT_FAILURE);
	}
}

static int	make_command_proccess(t_com_node *command, t_log_chan *new_chan, t_log_chan *old_chan)
{
	pid_t			fork_pid;
	int				fork_status;

	if (!command || !old_chan || !new_chan)
		return (EXIT_FAILURE);

	fork_pid = fork();
	if (fork_pid == -1)
	{
		perror("fork create error");
		return (EXIT_FAILURE);
	}
	if (fork_pid == 0)
		exec_command(command, new_chan, old_chan);
	waitpid(fork_pid, &fork_status, 0);
	return (fork_status);
}

static void	*exec_node_fail(t_log_chan *new_chan, t_log_chan *old_chan)
{
	free_log_chan(new_chan);
	free_log_chan(old_chan);
	return (NULL);
}

t_log_chan		*exec_node(t_com_node *command, t_log_chan *old_chan)
{
	t_log_chan	*new_chan;
	
	new_chan = make_log_chan();
	if (!new_chan)
		return (exec_node_fail(new_chan, old_chan));
	if (make_command_proccess(command, new_chan, old_chan) == -1)
		return (exec_node_fail(new_chan, old_chan));
	if (close_write(new_chan) == -1)
		return (exec_node_fail(new_chan, old_chan));
	free_log_chan(old_chan);
	return (new_chan);
}