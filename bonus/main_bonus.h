/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:44:04 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/11 13:44:08 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_BONUS_H
# define MAIN_BONUS_H
# include <unistd.h>
# include <stdio.h>
# include "../src/pipex.h"

// HEREDOC
int	check_heredoc(char *input_path);
int	add_heredoc(t_com_queue *q, char *limiter);

// OUTPUT
int	add_output_heredoc(t_com_queue *queue, char *output_path, int is_heredoc);
#endif