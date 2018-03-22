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
#include "libft.h"

void			handle_poctal_flags(t_conversation *conversation,
								int len)
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
}

static int		print_value(t_conversation *conversation,
							int value, char *s, int len)
{
	int written;

	written = 0;
	if (value || conversation->precision != -1)
	{
		ft_putstr(s);
		written += len;
	}
	return (written);
}

static int		print_pointer(t_conversation *conversation,
							char *value_str, int len, int value)
{
	int written;
	int	after_width;

	written = 0;
	handle_poctal_flags(conversation, len);
	after_width = conversation->field_width - conversation->precision - len - 1;
	if (!value)
		after_width--;
	if (conversation->flags.alternative && value)
		after_width--;
	if (!conversation->flags.left_justified && !conversation->flags.zeros)
		written += ft_print_times((after_width < 0 ? 0 : after_width), ' ');
	ft_putchar('0');
	written++;
	ft_putchar(conversation->specifier == X ? 'X' : 'x');
	written++;
	if (value || conversation->precision != -1)
		written += ft_print_times(conversation->precision, '0');
	written += print_value(conversation, value, value_str, len);
	free(value_str);
	if (value || conversation->precision != -1)
		if (conversation->flags.left_justified && !conversation->flags.zeros)
			written += ft_print_times((after_width < 0 ? 0 : after_width), ' ');
	return (written);
}

int				ft_process_pointer(t_conversation *conversation,
							va_list args)
{
	int					written;
	long long			value;
	int					len;
	char				*result;

	written = 0;
	conversation->flags.alternative = 1;
	conversation->length_modifier = l;
	value = convert_uinteger(va_arg(args, long long), conversation);
	result = itoa_base(value, 16, conversation);
	if (value == 0)
		*result = '0';
	len = ft_strlen(result);
	return (print_pointer(conversation, result, len, value));
}
