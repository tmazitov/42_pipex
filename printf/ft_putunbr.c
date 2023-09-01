/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 18:45:51 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/02 15:50:37 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunbr(unsigned int num)
{
	int	result;

	result = 0;
	if (num / 10 > 0)
		result += ft_putunbr(num / 10);
	result += ft_putchar('0' + num % 10);
	return (result);
}
