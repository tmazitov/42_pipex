/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:44:34 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/01 14:13:12 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void exec_command(t_com_node *com, t_log_chan *new_chan, t_log_chan *old_chan, char **envp)
{
	// Read input
	dup2(old_chan->side[0], STDIN_FILENO);
	close_read(old_chan);
	dup2(new_chan->side[1], STDOUT_FILENO);
	close_write(new_chan);
	execve(com->command_path, com->args, envp);
}

static int	make_command_proccess(t_com_node *com, t_log_chan *new_chan, t_log_chan *old_chan, char **envp)
{
	pid_t	fork_pid;
	int		status;
	
	if (!com || !old_chan || !new_chan)
		return (EXIT_FAILURE);
	fork_pid = fork();
	if (fork_pid == -1)
		return (-1);
	else if (fork_pid == 0)
		exec_command(com, new_chan, old_chan, envp);
	waitpid(fork_pid, &status, 0);
	printf("status: %d\n", WEXITSTATUS(status));
	return (WEXITSTATUS(status));
}

// static void	*exec_node_fail(t_log_chan *new_chan, t_log_chan *old_chan)
// {
// 	free_log_chan(new_chan);
// 	free_log_chan(old_chan);
// 	return (NULL);
// }

t_log_chan		*exec_node(t_com_node *command, t_log_chan *old_chan, char **envp)
{
	t_log_chan	*new_chan;
	
	new_chan = make_log_chan();
	if (!new_chan)
	{
		free_log_chan(old_chan);
		return (new_chan);		
	}
	new_chan->status = make_command_proccess(command, new_chan, old_chan, envp);
	if (new_chan->status)
	{
		free_log_chan(old_chan);
		return (new_chan);	
	}
	close_write(new_chan);
	free_log_chan(old_chan);
	return (new_chan);
}