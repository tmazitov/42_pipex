/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:27:32 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/22 21:49:49 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **envp) {
	char			*inputFilePath;
	char			*outputFilePath;
	int				counter;
	t_com_queue		*com_queue;
	t_com_node		*com_node;
	t_log_session	*log_session;
	if (argc < 3)
	{
		perror("Invalid count of arguments");
		return 1;
	}
	inputFilePath = argv[1];
	outputFilePath = argv[argc - 1];
	com_queue = make_queue(argv+2, getenv("PATH"), argc - 3);
	log_session = NULL;
	if (!com_queue)
	{
		perror("Invalid creation of the command list");
		return 1;
	}
	com_node = get_node(com_queue);
	while (com_node && com_node->command_name)
	{
		printf("command: %s\n", com_node->command_name);
		counter = 0;
		printf("	path: %s\n", com_node->command_path); 	
		while(com_node->args[counter])
			printf("	arg: %s\n", com_node->args[counter++]);
		log_session = exec_node(com_node, log_session);
		com_node = get_node(com_queue);
	}

    return 0;
}
