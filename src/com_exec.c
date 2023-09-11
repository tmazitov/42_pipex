/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:44:34 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/11 10:18:11 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	command_proc(t_com_node *command, char **envp, t_com_queue *q)
{
	t_log_chan	*input;
	t_log_chan	*output;
	int			status;

	input = command->in_chan;
	output = command->out_chan;
	if (!input || !output)
	{
		free_queue(q);
		panic(NULL, 1);
	}
	dup2(input->side[0], STDIN_FILENO);
	dup2(output->side[1], STDOUT_FILENO);
	close_write(command->out_chan);
	close_read(command->in_chan);
	close_write(command->in_chan);
	close_read(command->out_chan);
	status = execve(command->path, command->args, envp);
	free_queue(q);
	exit(status);
}

void	run_command_proc(t_com_node *command, char **envp, t_com_queue *q)
{
	pid_t	proc_id;

	if (!command || !envp)
		return ;
	proc_id = fork();
	if (proc_id == -1)
		return ;
	if (proc_id == 0)
		command_proc(command, envp, q);
	command->proc_id = proc_id;
	close_write(command->out_chan);
	close_read(command->in_chan);
}
