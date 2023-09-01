/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:40:10 by tmazitov          #+#    #+#             */
/*   Updated: 2023/08/02 16:40:32 by tmazitov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_putnbr(int num);
int		ft_puthex(unsigned long long address);
int		ft_putunbr(unsigned int num);
int		ft_print_up_hex( unsigned int address);
int		ft_print_low_hex( unsigned int address);
int		ft_printf(const char *format_str, ...);

#endif	