/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:36:04 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/05 21:55:45 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

void	check_argv(char *input_path, t_com_queue *commands)
{
	int			input_file_is_unavailable;
	char		*undefind_command;
	int			last_path_is_unavailable;
	t_com_node	*command;

	input_file_is_unavailable = check_input(input_path);
	if (input_file_is_unavailable)
		ft_printf("pipex: no such file or directory: %s\n", input_path);
	undefind_command = NULL;
	command = get_first(commands);
	while (command)
	{
		if (!command->command_path)
			ft_printf("pipex: command not found: %s\n", command->command_name);
		if (!command->command_path)
			undefind_command = command->command_name;
		command = command->next;
	}
	command = get_last(commands);
	last_path_is_unavailable = command->command_name == undefind_command;
	if (input_file_is_unavailable || last_path_is_unavailable)
		free_queue(commands);
	if (input_file_is_unavailable && last_path_is_unavailable)
		exit(127);
	else if (input_file_is_unavailable && !last_path_is_unavailable)
		exit(0);
	else if (!input_file_is_unavailable && last_path_is_unavailable)
		exit(127);
}

t_log_chan	*run(t_com_queue *commands, char **envp, int count)
{
	t_com_node	*command;
	// int			counter;
	pid_t		pid;
	int			status;
	
	command = get_node(commands);
	while (command)
	{
     	run_command_proc(command, envp);
		if (command->proc_id == -1)
		{
			free_queue(commands);
			panic("execute command error", 1);
		}
		// print_node(command);
		command = get_node(commands);
	}
	// counter = 0;
	// while (counter < count)
	// {
	// 	pid = wait(&status);
	// 	command = get_node_by_pid(commands, pid);
	// 	printf("command done: %s\n", command->command_name);
	// 	stop_proc(command);
	// 	counter++;	
	// }
	free_queue(commands);
	return (NULL);
}

t_log_chan	*make_exec_commands(char **argv, int com_count, char **envp)
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
	if (add_output(commands, output_path))
	{
		free_queue(commands);
		panic("open output file error", 1);
	}
	if (add_input(commands, input_path))
	{
		free_queue(commands);
		panic("open input file error", 1);
	}
	return (run(commands, envp, com_count));
}

int	main(int argc, char **argv, char **envp)
{
	t_log_chan		*log_chan;
	int				status;
	int				output;

	if (argc != 5)
		panic("invalid count of arguments", 0);
	output = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (output < 0)
		panic("can not to create output file", 1);
	close(output);
	log_chan = make_exec_commands(argv, argc - 3, envp);
	// status = make_output(argv[argc - 1], log_chan);
	// free_log_chan(log_chan);
	return (status);
}
