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

char    *find_command_path(const char *command_name, char* env_path) 
{	
    char    **env_path_dirs;
    char    *command_path;
    char    *sep;
    char    *finished_dir;
    int	    counter;

    if (!env_path)
        return NULL;
    sep = malloc(sizeof(char)*2);
    if (!sep)
	return (NULL);
    sep[0] = '/';
    sep[1] = '\0';
    counter = 0;
    env_path_dirs = ft_split(env_path, ':');
    while (env_path_dirs[counter]) {
        finished_dir = ft_strjoin(env_path_dirs[counter], sep);
	command_path = ft_strjoin(finished_dir, command_name);
	free(finished_dir);
        if (access(command_path, X_OK) == 0) {
	    free(sep);
            free_split(env_path_dirs);
            return (command_path);
        }
        free(command_path);
        counter++;
    }
    free_split(env_path_dirs);
    return (NULL); // Program not found in any directory in PATH
}
