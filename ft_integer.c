/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_integer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatsuk <amatsuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 15:56:32 by amatsuk           #+#    #+#             */
/*   Updated: 2018/03/08 13:35:22 by amatsuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long			convert_integer(long long value,
									t_conversation *conversation)
{
	int			int_value;
	short		short_value;
	signed char	char_value;

	if ((conversation->length_modifier == none)
		&& (value > 2147483647 || value < -2147483648))
	{
		int_value = (int)value;
		return ((intmax_t)int_value);
	}
	if (conversation->length_modifier == hh && (value < -127 || value > 127))
	{
		char_value = (signed char)value;
		return ((long long)char_value);
	}
	if (conversation->length_modifier == h && (value < -32767 || value > 32767))
	{
		short_value = (short)value;
		return ((long long)short_value);
	}
	return (value);
}

void				handle_flags(t_conversation *conversation,
								int len, long long value)
{
	if (conversation->precision < 0)
		conversation->precision = 0;
	else if (conversation->precision == 0 && conversation->precision_exist)
		conversation->precision = -1;
	if (conversation->flags.sign)
		conversation->flags.space = 0;
	if (value < 0)
	{
		conversation->flags.sign = 1;
		conversation->flags.space = 0;
	}
	if (conversation->precision != 0)
		conversation->flags.zeros = 0;
	if (conversation->flags.left_justified)
		conversation->flags.zeros = 0;
	if (len - conversation->precision >= 0)
	{
		if (conversation->precision != -1)
			conversation->precision = 0;
	}
	else
		conversation->precision = conversation->precision - len;
	if (value > 0 && conversation->precision == -1)
		conversation->precision = 0;
}

static	int			print_integer(t_conversation *conversation,
									int len, long long value)
{
	int written;
	int	after_width;

	written = 0;
	after_width = conversation->field_width - conversation->flags.sign
				- conversation->flags.space - conversation->precision - len;
	if (!conversation->flags.left_justified && !conversation->flags.zeros)
		written += ft_print_times((after_width < 0 ? 0 : after_width), ' ');
	if (conversation->flags.sign)
	{
		ft_putchar((value < 0 ? '-' : '+'));
		written++;
	}
	if (conversation->flags.zeros)
		written += ft_print_times((after_width < 0 ? 0 : after_width), '0');
	written += ft_print_times(conversation->precision, '0');
	if (conversation->precision != -1)
	{
		ft_putbignbr(value);
		written += len;
	}
	if (conversation->flags.left_justified && !conversation->flags.zeros)
		written += ft_print_times((after_width < 0 ? 0 : after_width), ' ');
	return (written);
}

unsigned long long	cast_integer(t_conversation *conversation, long long value)
{
	int		int_value;
	short	short_value;
	char	char_value;

	if ((conversation->length_modifier == none)
		&& (value > 2147483647 || value < -2147483648))
	{
		int_value = (int)value;
		return ((intmax_t)int_value);
	}
	if (conversation->length_modifier == hh && (value < -127 || value > 127))
	{
		char_value = (signed char)value;
		return ((long long)char_value);
	}
	if (conversation->length_modifier == h && (value < -32767 || value > 32767))
	{
		short_value = (short)value;
		return ((long long)short_value);
	}
	return (value);
}

int					process_integer(t_conversation *conversation, va_list args,
									char c)
{
	int					written;
	long long			value;
	int					len;

	written = 0;
	if (c == 'D')
		conversation->length_modifier = l;
	value = convert_integer(va_arg(args, long long), conversation);
	len = get_integer_size(value);
	handle_flags(conversation, (value < 0 ? (len - 1) : len), value);
	if (conversation->flags.space)
	{
		written++;
		ft_putchar(' ');
	}
	written += print_integer(conversation,
							(value < 0 ? (len - 1) : len), value);
	return (written);
}
