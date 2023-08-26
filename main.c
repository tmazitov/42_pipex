/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:27:32 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/26 22:50:24 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	write_output(int output_fd, t_log_chan *chan)
{
	char	**chan_payload;
	int		counter;

	chan_payload = get_chan_payload(chan);
	if (!chan_payload)
		return ;
	printf("hi!\n");
	
	counter = 0;
	while (chan_payload[counter])
	{
		write(output_fd, chan_payload[counter], ft_strlen(chan_payload[counter]));
		write(output_fd, "\n", 1);
		counter++;
	}
}

int main(int argc, char **argv, char **envp) {
	int				input_fd;
	int				output_fd;
	int				counter;
	t_com_queue		*commands;
	t_com_node		*next_command;
	t_log_chan		*log_chan;
	if (argc < 3)
	{
		perror("Invalid count of arguments");
		return 1;
	}
	input_fd = open(argv[1], O_RDONLY);
	if (!input_fd)
		return EXIT_FAILURE;
	log_chan = make_log_chan();
	if (!log_chan)
	{
		close(input_fd);
		return EXIT_FAILURE;
	}
	close_read(log_chan);
	if (set_read(log_chan, input_fd) == -1)
	{
		free_log_chan(log_chan);
		return EXIT_FAILURE;
	}
	if (close_write(log_chan) == -1)
	{
		free_log_chan(log_chan);
		return EXIT_FAILURE;
	}
	commands = make_queue(argv+2, getenv("PATH"), argc - 3);
	if (!commands)
	{
		free_log_chan(log_chan);
		perror("Invalid creation of the command queue");
		return EXIT_FAILURE;
	}
	next_command = get_node(commands);
	while (next_command && next_command->command_path)
	{
		printf("com: %s\n", next_command->command_name);
		printf("\tpath: %s\n", next_command->command_path);
		log_chan = exec_command(next_command, log_chan);
		if (!log_chan)
		{
			// free_queue(commands);
			close(input_fd);
			return EXIT_FAILURE;
		}
		next_command = get_node(commands);
	}
	output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT);
	if (!output_fd)
	{
		close(output_fd);
		return EXIT_FAILURE;
	}
	write_output(output_fd, log_chan);
	close(output_fd);
	close(input_fd);
    return 0;
}
