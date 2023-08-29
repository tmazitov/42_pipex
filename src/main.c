/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:27:32 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/29 13:59:42 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_log_chan *make_exec_commands(char **com_raw, int com_count, char *path, t_log_chan *data_chan)
{
	t_com_node		*next_command;
	t_com_queue		*commands;

	commands = make_queue(com_raw, path, com_count);
	if (!commands)
		return (free_log_chan(data_chan));
	next_command = get_node(commands);
	while (next_command && next_command->command_path)
	{
		data_chan = exec_node(next_command, data_chan);
		if (!data_chan)
		{
			free_queue(commands);
			return (free_log_chan(data_chan));			
		}
		next_command = get_node(commands);
	}
	free_queue(commands);
	return (data_chan);
}

int main(int argc, char **argv, char **envp) 
{
	t_log_chan		*log_chan;
	char			*path;
	
	if (argc < 5)
		return (EXIT_FAILURE);

	if (check_input(argv[1]) || check_output(argv[argc - 1]))
		return (EXIT_FAILURE);
	path = find_path(envp);
	if (!path)
		return (EXIT_FAILURE);
	log_chan = make_input(argv[1]);
	if (!log_chan)
		return (EXIT_FAILURE);
	log_chan = make_exec_commands(argv + 2, argc - 3, path, log_chan);
	if (!log_chan)
		return EXIT_FAILURE;
	if (make_output(argv[argc - 1], log_chan))
	{
		free_log_chan(log_chan);
		return(EXIT_FAILURE);
	}
    return (EXIT_SUCCESS);
}
