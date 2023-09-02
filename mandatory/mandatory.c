/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:36:04 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/02 23:10:36 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

void	check_argv(char *input_path, t_com_queue *commands)
{
	int	input_file_is_unavailable;
	int	commands_is_unavailable;
	t_com_node		*next_command;

	input_file_is_unavailable = check_input(input_path);
	if (input_file_is_unavailable)
	{
		ft_printf("no such file or directory: %s\n", input_path);
	}
	commands_is_unavailable = 0;
	next_command = commands->nodes;
	while (next_command)
	{
		if (!next_command->command_path)
		{
			commands_is_unavailable = 1;
			ft_printf("command not found: %s\n", next_command->command_name);
		}
		next_command = next_command->prev;
	}
	if (input_file_is_unavailable && commands_is_unavailable)
		exit(127);
	else if (input_file_is_unavailable && !commands_is_unavailable)
		exit(1);
	else if (!input_file_is_unavailable && commands_is_unavailable)
		exit(127);
}

t_log_chan *make_exec_commands(char **argv, int com_count, char **envp)
{
	t_com_node		*next_command;
	t_com_queue		*commands;
	char			*path;
	t_log_chan		*data_chan;


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
	next_command = get_node(commands);
	while (next_command)
	{
		data_chan = exec_node(next_command, data_chan, envp);
		if (!data_chan)
		{
			free_queue(commands);
			panic("execute command error", 1);
		}
		if (data_chan->status == 127)
			ft_printf("command not found: %s\n", next_command->command_name);
		free_node(next_command);
		next_command = get_node(commands);
	}
	free_queue(commands);
	return (data_chan);
}

int main(int argc, char **argv, char **envp) 
{
	t_log_chan		*log_chan;
	int				status;
	
	if (argc != 5)
	{
		ft_printf("invalid count of arguments: %d\n", argc);
		exit(0);
	}

	log_chan = make_exec_commands(argv, argc - 3, envp);
	status = make_output(argv[argc - 1], log_chan);
	free_log_chan(log_chan);
    return (status);
}
