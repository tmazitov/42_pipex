/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 23:00:50 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/20 23:10:34 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    free_split_res(char **split_res)
{
    while (*split_res)
    {
        free(*split_res);
        split_res++;
    }
    free(split_res);
}

char    *find_command_path(const char *command_name, char* env_path) 
{	
	char	**env_path_dirs;
    char    *command_path;
    char    sep[1];

    if (!env_path)
        return NULL;

    sep[0] = '/';
    env_path_dirs = ft_split(env_path, ':');
    while (*env_path_dirs) {

        command_path = ft_strjoin(*env_path_dirs, sep);
        command_path = ft_strjoin(command_path, command_name);

        if (access(command_path, X_OK) == 0) {
            free_split_res(env_path_dirs);
            return (command_path);
        }
        free(command_path);
        env_path_dirs++;
    }
    free_split_res(env_path_dirs);
    return (NULL); // Program not found in any directory in PATH
}