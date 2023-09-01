/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:27:32 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/01 14:06:12 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	data_chan = make_input(argv[1]);
	if (!data_chan)
		panic("make input chan error", 1);
	next_command = get_node(commands);
	while (next_command && next_command->command_path)
	{
		data_chan = exec_node(next_command, data_chan, envp);
		if (!data_chan || (data_chan && data_chan->status))
		{
			free_queue(commands);
			panic("execute command error", 1);
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
		panic("many arguments error", 0);
	if (check_input(argv[1]))
		panic("access input and output error", 0);
	log_chan = make_exec_commands(argv, argc - 3, envp);
	if (make_output(argv[argc - 1], log_chan))
	{
		free_log_chan(log_chan);
		panic("write output error", 1);
	}
    return (EXIT_SUCCESS);
}
