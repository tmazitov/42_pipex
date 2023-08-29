/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:10:47 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/29 20:58:25 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

char    *find_command_path(const char *command_name, char* env_path);
char	**ft_split(char const *str, char ch);
char    *find_path(char **envp);
void	*free_split(char **split_result);
char	*ft_strjoin(char const *str1, char const *str2);
char	*ft_substr(char const *str, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	panic(char *message);
#endif // !UTILS_H
