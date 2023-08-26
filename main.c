/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:27:32 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/26 15:30:24 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	write_output(int output_fd, t_log_chan *chan)
{
	char	**chan_payload;
	int		counter;

	printf("get chan payload\n");
	chan_payload = get_chan_payload(chan);
	if (!chan_payload)
		return ;
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
	t_com_queue		*com_queue;
	t_com_node		*com_node;
	t_log_chan		*log_chan;
	if (argc < 3)
	{
		perror("Invalid count of arguments");
		return 1;
	}
	input_fd = open(argv[1], O_RDONLY);
	if (!input_fd)
		return EXIT_FAILURE;

	com_queue = make_queue(argv+2, getenv("PATH"), argc - 3);
	if (!com_queue)
	{
		close(input_fd);
		perror("Invalid creation of the command queue");
		return EXIT_FAILURE;
	}
	log_chan = make_log_chan();
	if (!log_chan)
	{
		close(input_fd);
		return EXIT_FAILURE;
	}
	log_chan->side[0] = input_fd;
	close(log_chan->side[1]);
	com_node = get_node(com_queue);
	while (com_node && com_node->command_name)
	{
		printf("command: %s\n", com_node->command_name);
		counter = 0;
		printf("	path: %s\n", com_node->command_path);
		while(com_node->args[counter])
			printf("	arg: %s\n", com_node->args[counter++]);
		log_chan = exec_command(com_node, log_chan);
		if (!log_chan)
		{
			close(input_fd);
			return EXIT_FAILURE;
		}
		com_node = get_node(com_queue);
	}
	output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT);
	if (!output_fd)
	{
		close(output_fd);
		return EXIT_FAILURE;
	}
	printf("end of the while\n");
	write_output(output_fd, log_chan);
	close(output_fd);
	close(input_fd);
    return 0;
}
