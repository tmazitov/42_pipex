/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:27:32 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/29 21:16:25 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_log_chan *make_exec_commands(char **com_raw, int com_count, char **envp, t_log_chan *data_chan)
{
	t_com_node		*next_command;
	t_com_queue		*commands;
	char			*path;

	path = find_path(envp);
	if (!path)
	{
		free_log_chan(data_chan);
		panic("find path error");
	}
	commands = make_queue(com_raw, path, com_count);
	if (!commands)
	{
		free_log_chan(data_chan);
		panic("make commands queue error");
	}
	next_command = get_node(commands);
	while (next_command && next_command->command_path)
	{
		data_chan = exec_node(next_command, data_chan, envp);
		if (!data_chan)
		{
			free_queue(commands);
			panic("execute command error");
		}
		next_command = get_node(commands);
	}
	free_queue(commands);
	return (data_chan);
}

int main(int argc, char **argv, char **envp) 
{
	t_log_chan		*log_chan;
	
	if (argc != 5)
		panic("many arguments error");
	// if (check_input(argv[1]) || check_output(argv[argc - 1]))
	// 	panic("access input and output error");
	log_chan = make_input(argv[1]);
	if (!log_chan)
		panic("make input chan error");
	log_chan = make_exec_commands(argv + 2, argc - 3, envp, log_chan);
	if (make_output(argv[argc - 1], log_chan))
	{
		free_log_chan(log_chan);
		panic("write output error");
	}
    return (EXIT_SUCCESS);
}
