/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 13:49:32 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/29 13:50:11 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	size_t	counter;
	int		result;

	counter = 0;
	result = 0;
	while ((str1[counter] || str2[counter]) && counter < num)
	{
		if (str1[counter] != str2[counter])
		{
			result = (unsigned char)str1[counter]
				- (unsigned char)str2[counter];
			return (result);
		}
		counter++;
	}
	if (num != counter)
		result = (unsigned char)str1[counter] - (unsigned char)str2[counter];
	return (result);
}


char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	counter;
	int		substr_is_same;
	size_t	little_len;

	if (!*little)
		return ((char *)big);
	little_len = ft_strlen(little);
	counter = 0;
	substr_is_same = 0;
	while (big[counter] && counter < len)
	{
		if (big[counter] == little[0])
		{
			substr_is_same = ft_strncmp(&big[counter], little, little_len);
			if (substr_is_same == 0 && counter + little_len <= len)
				return (&((char *)big)[counter]);
		}
		counter++;
	}
	return (0);
}
