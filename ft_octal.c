/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_octal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatsuk <amatsuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:34:41 by amatsuk           #+#    #+#             */
/*   Updated: 2018/03/08 18:56:01 by amatsuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			handle_octal_flags(t_conversation *conversation,
								int len, long long value)
{
	if (conversation->precision < 0)
		conversation->precision = 0;
	else if (conversation->precision == 0 && conversation->precision_exist)
		conversation->precision = -1;
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
	if (conversation->flags.alternative && conversation->precision < len
		&& value)
		conversation->precision++;
	if (conversation->flags.alternative && conversation->precision < len
		&& !value)
		conversation->precision = 0;
}

char			*itoa_base(unsigned long long value,
							int base, t_conversation *conversation)
{
	unsigned long long	i;
	char				*output;
	int					len;
	char				*base_array;

	len = 0;
	base_array = "0123456789abcdef";
	if (conversation->specifier == X)
		base_array = "0123456789ABCDEF";
	i = value;
	while (i != 0)
	{
		len++;
		i = i / base;
	}
	output = (char*)malloc(sizeof(char) * (len + 1));
	*(output + len) = '\0';
	i = value;
	while (i != 0)
	{
		*(output + len - 1) = *(base_array + (i % base));
		len--;
		i = i / base;
	}
	return (output);
}

static int		print_value(t_conversation *conversation,
							int value, char *s, int len)
{
	int written;

	written = 0;
	if (conversation->precision != -1 || value != 0)
	{
		if (conversation->flags.alternative && value
			&& conversation->specifier != o && !conversation->flags.zeros)
		{
			ft_putchar(conversation->specifier == X ? 'X' : 'x');
			written++;
		}
		if (conversation->precision != 1
			|| ft_strlen(s) != 1 || !conversation->precision_exist)
		{
			ft_putstr(s);
			written += len;
		}
	}
	free(s);
	return (written);
}

static int		print_octal(t_conversation *cc,
							char *value_str, int len, int value)
{
	int written;
	int	after_width;

	written = 0;
	after_width = cc->field_width - cc->precision - len;
	if (cc->flags.alternative && value && cc->specifier != o)
		after_width--;
	if (!cc->flags.left_justified && !cc->flags.zeros)
		written += ft_print_times((after_width < 0 ? 0 : after_width), ' ');
	if (cc->flags.zeros)
	{
		if (cc->flags.alternative && value && cc->specifier != o)
		{
			ft_putchar('0');
			ft_putchar(cc->specifier == X ? 'X' : 'x');
			written += 2;
			after_width--;
		}
		written += ft_print_times((after_width < 0 ? 0 : after_width), '0');
	}
	written += ft_print_times(cc->precision, '0');
	written += print_value(cc, value, value_str, len);
	if (cc->flags.left_justified && !cc->flags.zeros)
		written += ft_print_times((after_width < 0 ? 0 : after_width), ' ');
	return (written);
}

int				process_octal_hex(t_conversation *cc, va_list args, char c)
{
	long long			v;
	int					len;
	char				*result;

	cc->specifier = o;
	if (c == 'X')
		cc->specifier = X;
	if (c == 'x')
		cc->specifier = x;
	if (c == 'O')
		v = va_arg(args, long long);
	else
		v = convert_uinteger(va_arg(args, long long), cc);
	if (cc->precision == 0 && cc->precision_exist == 1
		&& v == 0 && cc->specifier != o)
	{
		ft_print_times(cc->field_width, ' ');
		return (cc->field_width);
	}
	result = (cc->specifier == o ? itoa_base(v, 8, cc) : itoa_base(v, 16, cc));
	if (v == 0)
		*result = '0';
	len = ft_strlen(result);
	handle_octal_flags(cc, len, v);
	return (print_octal(cc, result, len, v));
}
