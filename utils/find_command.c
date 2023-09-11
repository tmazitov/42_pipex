/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:54:17 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/11 10:38:28 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../get_next_line/get_next_line.h"

static char	*make_separator(void)
{
	char	*separator;

	separator = malloc(sizeof(char) * 2);
	if (!separator)
		return (NULL);
	separator[0] = '/';
	separator[1] = '\0';
	return (separator);
}

static void	*free_null(char *str)
{
	if (str)
		free(str);
	return (NULL);
}

static char	*check_path(char *path, char *command_name)
{
	char	*directory;
	char	*command_path;
	char	*separator;
	int		ok;

	separator = make_separator();
	if (!separator)
		return (NULL);
	directory = ft_strjoin(path, separator);
	if (!directory)
		return (free_null(separator));
	command_path = ft_strjoin(directory, command_name);
	free(directory);
	free(separator);
	if (!command_path)
		return (NULL);
	ok = access(command_path, X_OK);
	if (ok == -1)
		return (free_null(command_path));
	return (command_path); 
}

char	*find_command_path(char *command_name, char *env_path)
{
	char	**env_path_dirs;
	char	*result;
	int		counter;

	if (!env_path || !command_name)
		return (NULL);
	if (ft_strchr(command_name, '/'))
		return (command_name);
	counter = 0;
	env_path_dirs = ft_split(env_path, ':');
	while (env_path_dirs[counter])
	{
		result = check_path(env_path_dirs[counter], command_name);
		if (result)
		{
			free_split(env_path_dirs);
			return (result);
		}
		counter++;
	}
	free_split(env_path_dirs);
	return (NULL);
}

char	*find_path(char **envp)
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
