/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:44:34 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/05 21:49:17 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	command_proc(t_com_node *command, char **envp)
{
	t_log_chan	*input;
	t_log_chan	*output;

	input = command->in_chan;
	output = command->out_chan;
	dup2(input->side[0], STDIN_FILENO);
	close_read(input);
	dup2(output->side[1], STDOUT_FILENO);
	close_write(output);
	execve(command->command_path, command->args, envp);
}

// void test_read(t_log_chan *chan)
// {
// 	char	buffer[10];
// 	read( chan->side[0], buffer, 10);
// 	printf("BUFF: (%s)\nEND\n", buffer);
// }


void stop_proc(t_com_node *command)
{
	if (command->prev && command->prev->proc_in_progress)
		stop_proc(command->prev);
	free_log_chan(command->in_chan);
	command->proc_in_progress = 0;
}

static void	support_proc(t_com_node *command, char **envp)
{
	pid_t	proc_id;

	// test_read(command->in_chan);
	proc_id = fork();
	if (proc_id == -1)
		return ;
	else if (proc_id == 0)
		command_proc(command, envp);
	waitpid(proc_id, &command->proc_status, 0);
	// stop_proc(command);
	// free_log_chan(command->in_chan);
	// free_log_chan(command->out_chan);
	exit(command->proc_status);
}

void	run_command_proc(t_com_node *command, char **envp)
{
	pid_t	proc_id;

	if (!command || !envp)
		return ;
	command->proc_in_progress = 1;
	proc_id = fork();
	if (proc_id == -1)
		return ;
	else if (proc_id == 0)
		support_proc(command, envp);
	command->proc_id = proc_id;
	close_write(command->out_chan);
}
