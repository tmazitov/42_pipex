/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:15:18 by tmazitov          #+#    #+#             */
/*   Updated: 2023/09/01 19:16:59 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_type(const char *format_str, va_list args)
{
	if (*format_str == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (*format_str == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (*format_str == 'p')
		return (ft_puthex(va_arg(args, unsigned long long)));
	if (*format_str == 'd')
		return (ft_putnbr(va_arg(args, int)));
	if (*format_str == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (*format_str == 'u')
		return (ft_putunbr(va_arg(args, unsigned int)));
	if (*format_str == 'x')
		return (ft_print_low_hex(va_arg(args, unsigned int)));
	if (*format_str == 'X')
		return (ft_print_up_hex(va_arg(args, unsigned int)));
	if (*format_str == '%')
		return (ft_putchar('%'));
	return (-1);
}

int	ft_printf(const char *format_str, ...)
{
	int		chars;
	int		t_print_result;
	va_list	args;

	if (!format_str)
		return (0);
	chars = 0;
	va_start(args, format_str);
	while (*format_str)
	{
		if (*format_str == '%' && *(format_str + 1))
		{
			format_str++;
			t_print_result = ft_print_type(format_str, args);
			chars += t_print_result;
			if (t_print_result != -1)
			{
				format_str++;
				continue ;
			}
		}
		chars += ft_putchar(*format_str++);
	}
	va_end(args);
	return (chars);
}
