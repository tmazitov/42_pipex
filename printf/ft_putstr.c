/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:46:17 by tmazitov          #+#    #+#             */
/*   Updated: 2023/07/17 15:29:13 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	int	result;

	result = 0;
	if (!s)
		return (ft_putstr("(null)"));
	while (*s)
		result += ft_putchar(*s++);
	return (result);
}
