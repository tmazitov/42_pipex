/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:44:34 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/07 19:19:02 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	command_proc(t_com_node *command, char **envp)
{
	t_log_chan	*input;
	t_log_chan	*output;
	int			status;

	input = command->in_chan;
	output = command->out_chan;
	if (!input || !output)
	{
		close_write(command->out_chan);
		close_read(command->in_chan);
		close_write(command->in_chan);
		close_read(command->out_chan);
		panic(NULL, 1);
	}
	dup2(input->side[0], STDIN_FILENO);
	dup2(output->side[1], STDOUT_FILENO);
	close_write(command->out_chan);
	close_read(command->in_chan);
	close_write(command->in_chan);
	close_read(command->out_chan);
	status = execve(command->path, command->args, envp);
	exit(status);
}

void	run_command_proc(t_com_node *command, char **envp)
{
	pid_t	proc_id;

	if (!command || !envp)
		return ;
	proc_id = fork();
	if (proc_id == -1)
		return ;
	else if (proc_id == 0)
		command_proc(command, envp);
	command->proc_id = proc_id;
	close_write(command->out_chan);
	close_read(command->in_chan);
}
