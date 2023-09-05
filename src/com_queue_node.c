/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_queue_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:35:47 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/05 20:47:56 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_com_node	*make_node(char *command_line, char *env_path)
{
	t_com_node	*node;
	char		**command_parts;

	if (!command_line)
		return (NULL);
	node = malloc(sizeof(t_com_node));
	if (!node)
		return (NULL);
	command_parts = ft_split(command_line, ' ');
	if (!command_parts)
	{
		free_node(node);
		return (NULL);
	}
	node->command_name = command_parts[0];
	node->args = command_parts;
	node->next = NULL;
	node->prev = NULL;
	node->command_path = find_command_path(command_parts[0], env_path);
	node->in_chan = NULL;
	node->out_chan = NULL;
	node->proc_id = -1;
	node->proc_status = 0;
	node->proc_in_progress = 0;
	return (node);
}

void	set_in_chan(t_com_node *node, t_log_chan *chan)
{
	node->in_chan = chan;
}

void	set_out_chan(t_com_node *node, t_log_chan *chan)
{
	node->out_chan = chan;
}
void	print_node(t_com_node *node)
{
	int	counter;

	if (!node)
		return ;
	counter = 0;
	ft_printf("node: %p\n", node);
	ft_printf("\tcommand:\t%s\n", node->command_name);
	ft_printf("\tpath:\t\t%s\n", node->command_path);
	ft_printf("\targs:\n");
	while (node->args[counter])
		ft_printf("\t\t# %s\n", node->args[counter++]);
	ft_printf("\tnext:\t\t%p\n", node->next);
	ft_printf("\tprev:\t\t%p\n", node->prev);
	ft_printf("\tpid:\t\t%d\n", node->proc_id);
	ft_printf("\tin_chan:\t\t%p\n", node->in_chan);
	ft_printf("\tout_chan:\t\t%p\n", node->out_chan);
}

void	*free_node(t_com_node *node)
{
	if (!node)
		return (NULL);
	if (node->args)
		free_split(node->args);
	node->next = NULL;
	node->prev = NULL;
	free(node);
	return (NULL);
}
