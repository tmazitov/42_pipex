/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:36:04 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/02 22:31:53 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

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
		panic("many arguments error", 0);
	if (check_input(argv[1]))
		panic("access input and output error", 0);
	log_chan = make_exec_commands(argv, argc - 3, envp);
	status = make_output(argv[argc - 1], log_chan);
	free_log_chan(log_chan);
    return (status);
}
