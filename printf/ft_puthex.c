/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:40:26 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/04 18:53:02 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_low_hex(unsigned int address)
{
	int		result;
	char	*dictionary;

	result = 0;
	dictionary = "0123456789abcdef";
	if (address / 16 != 0)
		result += ft_print_low_hex(address / 16);
	return (result + ft_putchar(dictionary[address % 16]));
}

int	ft_print_low_hex_long(unsigned long long address)
{
	int		result;
	char	*dictionary;

	result = 0;
	dictionary = "0123456789abcdef";
	if (address / 16 != 0)
		result += ft_print_low_hex_long(address / 16);
	return (result + ft_putchar(dictionary[address % 16]));
}

int	ft_print_up_hex(unsigned int address)
{
	int		result;
	char	*dictionary;

	result = 0;
	dictionary = "0123456789ABCDEF";
	if (address / 16 != 0)
		result += ft_print_up_hex(address / 16);
	return (result + ft_putchar(dictionary[address % 16]));
}

int	ft_puthex(unsigned long long address)
{
	int	result;

	result = 0;
	result += ft_putstr("0x");
	result += ft_print_low_hex_long(address);
	return (result);
}

// 16 chars 
// 0-9 - same like decimal
// 10-15 - A, B, C, D, E, F  same a, b, c, d, e, f