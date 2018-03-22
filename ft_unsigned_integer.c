/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_integer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatsuk <amatsuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 10:44:02 by amatsuk           #+#    #+#             */
/*   Updated: 2018/03/08 15:50:01 by amatsuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long int	convert_uinteger(unsigned long long int value,
										t_conversation *conversation)
{
	if ((conversation->length_modifier == h) &&
		(conversation->specifier != U) && (value > 65535))
		return ((unsigned long long)((unsigned short)value));
	if ((conversation->length_modifier == none) &&
		(conversation->specifier != U) && (value > 65535))
		return ((unsigned long long)((unsigned int)value));
	if ((conversation->length_modifier == hh) &&
		(conversation->specifier != U) && (value > 255))
		return ((unsigned long long)((unsigned char)value));
	if ((conversation->length_modifier == l) && (value > 4294967295))
		return ((unsigned long long)((unsigned long)value));
	return (value);
}

static	int				print_linteger(t_conversation *conversation,
									int len, unsigned long long value)
{
	int written;
	int	after_width;

	written = 0;
	after_width = conversation->field_width
					- conversation->precision - len;
	if (!conversation->flags.left_justified && !conversation->flags.zeros)
		written += ft_print_times((after_width < 0 ? 0 : after_width), ' ');
	if (conversation->flags.zeros)
		written += ft_print_times((after_width < 0 ? 0 : after_width), '0');
	written += ft_print_times(conversation->precision, '0');
	if (conversation->precision != -1)
	{
		ft_putbiglnbr(value);
		written += len;
	}
	if (conversation->flags.left_justified && !conversation->flags.zeros)
		written += ft_print_times((after_width < 0 ? 0 : after_width), ' ');
	return (written);
}

int						process_linteger(t_conversation *conversation,
												va_list args, char c)
{
	long long			value;
	int					len;

	conversation->specifier = U;
	if (c == 'u')
		conversation->specifier = u;
	if (c == 'x')
		conversation->specifier = x;
	if (c == 'X')
		conversation->specifier = X;
	value = convert_uinteger(va_arg(args, long long), conversation);
	len = get_linteger_size(value);
	if (conversation->precision == 0 && !value && conversation->precision_exist)
		return (ft_print_times(conversation->field_width, ' '));
	handle_flags(conversation, len, 1);
	return (print_linteger(conversation, len, value));
}
