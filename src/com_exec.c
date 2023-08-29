/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:44:34 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/29 20:58:40 by tmazitov         ###   ########.fr       */
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
	if (execve(com->command_path, com->args, envp) == -1)
		panic("fork execve error");
}

static int	make_command_proccess(t_com_node *com, t_log_chan *new_chan, t_log_chan *old_chan, char **envp)
{
	pid_t			fork_pid;

	if (!com || !old_chan || !new_chan)
		return (EXIT_FAILURE);
	fork_pid = fork();
	if (fork_pid == -1)
		return (EXIT_FAILURE);
	else if (fork_pid == 0)
		exec_command(com, new_chan, old_chan, envp);
	waitpid(fork_pid, NULL, 0);
	return (EXIT_SUCCESS);
}

static void	*exec_node_fail(t_log_chan *new_chan, t_log_chan *old_chan)
{
	free_log_chan(new_chan);
	free_log_chan(old_chan);
	return (NULL);
}

t_log_chan		*exec_node(t_com_node *command, t_log_chan *old_chan, char **envp)
{
	t_log_chan	*new_chan;
	
	new_chan = make_log_chan();
	if (!new_chan)
		return (exec_node_fail(new_chan, old_chan));
	if (make_command_proccess(command, new_chan, old_chan, envp))
		return (exec_node_fail(new_chan, old_chan));
	close_write(new_chan);
	free_log_chan(old_chan);
	return (new_chan);
}