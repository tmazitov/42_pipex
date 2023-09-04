/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 23:00:50 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/04 16:49:51 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../get_next_line/get_next_line.h"

char    *find_command_path(char *command_name, char* env_path) 
{	
    char    **env_path_dirs;
    char    *command_path;
    char    *sep;
    char    *finished_dir;
    int	    counter;

    if (!env_path || !command_name)
        return NULL;
    if (ft_strchr(command_name, '/'))
        return (command_name);
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
        if (!access(command_path, X_OK)) {
	        free(sep);
            free_split(env_path_dirs);
            return (command_path);
        }
        free(command_path);
        counter++;
    }
    free_split(env_path_dirs);
    return (NULL);
}

char    *find_path(char **envp)
{    
    if (!envp)
        return (NULL);
    while (*envp)
    {
        if (ft_strnstr(*envp, "PATH", 4))
            return (*envp + 5);
        envp++;
    }
    return (NULL);
}