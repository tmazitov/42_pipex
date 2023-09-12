/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:36:04 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/12 10:36:50 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/pipex.h"

void	check_argv(char *input_path, t_com_queue *commands)
{
	int			input_err;
	t_com_node	*command;

	input_err = check_input(input_path);
	if (input_err)
		ft_printf("pipex: no such file or directory: %s\n", input_path);
	command = get_first(commands);
	while (command)
	{
		if (!command->path)
		{
			if (!input_err || (input_err && command != get_first(commands)))
				ft_printf("pipex: command not found: %s\n", command->name);
			command->proc_status = 127;
		}
		command = command->next;
	}
}

void	run_commands(t_com_queue *commands, char **envp)
{
	t_com_node	*command;

	command = get_node(commands);
	while (command)
	{
		run_command_proc(command, envp, commands);
		if (command->proc_id == -1)
		{
			free_queue(commands);
			panic("execute command error", 1);
		}
		command = get_node(commands);
	}
}

int	wait_commands(t_com_queue *commands, int count)
{
	t_com_node	*command;
	int			counter;
	int			status;
	pid_t		pid;

	counter = 0;
	status = 0;
	while (counter < count)
	{
		pid = wait(&status);
		command = get_node_by_pid(commands, pid);
		if (command && !command->proc_status)
		{
			status = WEXITSTATUS(status);
			command->proc_status = status;
		}
		counter++;
	}
	command = get_last(commands);
	status = command->proc_status;
	free_queue(commands);
	return (status);
}

int	make_exec_commands(char **argv, int com_count, char **envp)
{
	t_com_queue	*commands;
	char		*path;
	char		*input_path;
	char		*output_path;

	input_path = argv[1];
	output_path = argv[com_count + 2];
	path = find_path(envp);
	if (!path)
		panic("find path error", 1);
	commands = make_queue(argv + 2, path, com_count);
	if (!commands)
		panic("make command queue error", 1);
	check_argv(argv[1], commands);
	add_input(commands, input_path);
	add_output(commands, output_path);
	run_commands(commands, envp);
	free_queue_relationship(commands);
	return (wait_commands(commands, com_count));
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		panic("invalid count of arguments", 0);
	return (make_exec_commands(argv, argc - 3, envp));
}
