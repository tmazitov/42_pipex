/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:36:04 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/04 19:08:54 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

void	check_argv(char *input_path, t_com_queue *commands)
{
	int			input_file_is_unavailable;
	int			commands_is_unavailable;
	t_com_node	*next_command;

	input_file_is_unavailable = check_input(input_path);
	if (input_file_is_unavailable)
	{
		ft_printf("pipex: no such file or directory: %s\n", input_path);
	}
	commands_is_unavailable = 0;
	next_command = get_first(commands);
	while (next_command)
	{
		commands_is_unavailable = !next_command->command_path;
		if (commands_is_unavailable)
			ft_printf("pipex: command not found: %s\n", 
				next_command->command_name);
		next_command = next_command->next;
	}
	if (input_file_is_unavailable && commands_is_unavailable)
		exit(127);
	else if (input_file_is_unavailable && !commands_is_unavailable)
		exit(0);
	else if (!input_file_is_unavailable && commands_is_unavailable)
		exit(127);
}

t_log_chan	*run(t_com_queue *commands, t_log_chan *chan, char **envp)
{
	t_com_node	*next_command;

	next_command = get_node(commands);
	while (next_command)
	{
		chan = exec_node(next_command, chan, envp);
		if (!chan)
		{
			free_queue(commands);
			panic("execute command error", 1);
		}
		free_node(next_command);
		next_command = get_node(commands);
	}
	free_queue(commands);
	return (chan);
}

t_log_chan	*make_exec_commands(char **argv, int com_count, char **envp)
{
	t_com_node	*next_command;
	t_com_queue	*commands;
	char		*path;
	t_log_chan	*data_chan;

	path = find_path(envp);
	if (!path)
		panic("find path error", 1);
	commands = make_queue(argv + 2, path, com_count);
	if (!commands)
		panic("make command queue error", 1);
	check_argv(argv[1], commands);
	data_chan = make_input(argv[1]);
	if (!data_chan)
		panic("make input chan error", 1);
	return (run(commands, data_chan, envp));
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
	status = make_output(argv[argc - 1], log_chan);
	free_log_chan(log_chan);
	return (status);
}
