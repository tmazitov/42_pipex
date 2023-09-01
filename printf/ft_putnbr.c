/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:53:53 by tmazitov          #+#    #+#             */
/*   Updated: 2023/07/17 15:28:08 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_nbr(int num)
{
	int	div;
	int	mod;
	int	result;

	result = 0;
	div = num / 10;
	mod = num % 10;
	if ((num > 0 && div > 0) || (num < 0 && div < 0))
		result += print_nbr(div);
	if (mod < 0)
		mod *= -1;
	result += ft_putchar('0' + mod);
	return (result);
}

int	ft_putnbr(int num)
{
	int	result;

	result = 0;
	if (num < 0)
		result += ft_putchar('-');
	result += print_nbr(num);
	return (result);
}
