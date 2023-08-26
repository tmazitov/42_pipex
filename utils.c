/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 18:04:22 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/26 19:55:15 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"

char	*ft_strjoin(char const *str1, char const *str2)
{
	char	*result;
	int		counter;

	counter = 0;
	if (!str1 || !str2)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!result)
		return (NULL);
	while (*str1)
		result[counter++] = *str1++;
	while (*str2)
		result[counter++] = *str2++;
	result[counter] = '\0';
	return (result);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	counter;
	size_t	str_len;
	size_t	sub_len;

	if (!str)
		return (NULL);
	str_len = ft_strlen(str);
	if (start + len <= str_len)
		sub_len = len;
	else if (str_len - 1 < start)
		sub_len = 0;
	else
		sub_len = str_len - start;
	sub_str = malloc(sizeof(char) * (sub_len + 1));
	if (!sub_str)
		return (NULL);
	counter = 0;
	while (counter < sub_len && str[counter + start])
	{
		sub_str[counter] = str[counter + start];
		counter++;
	}
	sub_str[sub_len] = '\0';
	return (sub_str);
}


char	**darr_union(char **darr1, char **darr2)
{
	int		counter1;
	int		counter2;
	int		counter_res;
	char	**result;

	if (!darr1 && !darr2)
		return (NULL);
	counter1 = 0;
	counter2 = 0;
	while (darr1 && darr1[counter1])
		counter1++;
	while (darr2 && darr2[counter2])
		counter2++;
	result = malloc(sizeof(char *) * (counter1 + counter2 + 1));
	if (!result)
		return (NULL);
	counter_res = 0;
	counter1 = 0;
	while (darr1 && darr1[counter1])
		result[counter_res++] = darr1[counter1++];
	counter2 = 0;
	while (darr2 && darr2[counter2])
		result[counter_res++] = darr2[counter2++];
	result[counter_res] = NULL;
	return (result);
}