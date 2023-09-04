/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:44:34 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/04 19:08:16 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec(t_com_node *com, t_log_chan *new, t_log_chan *old, char **e)
{
	dup2(old->side[0], STDIN_FILENO);
	close_read(old);
	dup2(new->side[1], STDOUT_FILENO);
	close_write(new);
	execve(com->command_path, com->args, e);
}

static int	fcomm(t_com_node *com, t_log_chan *new, t_log_chan *old, char **e)
{
	pid_t	fork_pid;
	int		status;

	if (!com || !new || !old)
		return (EXIT_FAILURE);
	fork_pid = fork();
	if (fork_pid == -1)
		return (-1);
	else if (fork_pid == 0)
		exec(com, new, old, e);
	waitpid(fork_pid, &status, 0);
	return (WEXITSTATUS(status));
}

t_log_chan	*exec_node(t_com_node *command, t_log_chan *old_chan, char **envp)
{
	t_log_chan	*new_chan;

	new_chan = make_log_chan();
	if (!new_chan)
	{
		free_log_chan(old_chan);
		return (NULL);
	}
	if (!command->command_path)
	{
		new_chan->status = 127;
		free_log_chan(old_chan);
		return (new_chan);
	}
	new_chan->status = fcomm(command, new_chan, old_chan, envp);
	close_write(new_chan);
	free_log_chan(old_chan);
	return (new_chan);
}
