/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatsuk <amatsuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 16:35:32 by amatsuk           #+#    #+#             */
/*   Updated: 2018/03/07 16:44:44 by amatsuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_2bytes(unsigned int wchar_int)
{
	ft_putchar(((wchar_int >> 6) & 63) | 192);
	ft_putchar((wchar_int & 63) | 128);
	return (2);
}

static int	ft_print_3bytes(unsigned int wchar_int)
{
	ft_putchar(((wchar_int >> 12) & 15) | 224);
	ft_putchar(((wchar_int >> 6) & 63) | 128);
	ft_putchar((wchar_int & 63) | 128);
	return (3);
}

static int	ft_print_4bytes(unsigned int wchar_int)
{
	ft_putchar(((wchar_int >> 18) & 7) | 240);
	ft_putchar(((wchar_int >> 12) & 63) | 128);
	ft_putchar(((wchar_int >> 6) & 63) | 128);
	ft_putchar((wchar_int & 63) | 128);
	return (4);
}

int			ft_print_wchar(wchar_t c, t_conversation *cc)
{
	unsigned int wchar_int;

	if (cc->length_modifier == l || cc->specifier == S)
	{
		ft_putchar((char)c);
		return (1);
	}
	wchar_int = c;
	if (wchar_int <= 127)
	{
		ft_putchar(wchar_int & 127);
		return (1);
	}
	else if (wchar_int <= 2047)
		return (ft_print_2bytes(wchar_int));
	else if (wchar_int <= 65535)
		return (ft_print_3bytes(wchar_int));
	else
		return (ft_print_4bytes(wchar_int));
}

int			ft_print_char(t_conversation *conversation, va_list args)
{
	int				i;
	unsigned char	c;
	int				written;

	i = 0;
	written = 0;
	if (!conversation->flags.left_justified)
		written += ft_print_times(conversation->field_width - 1, ' ');
	if (conversation->length_modifier == w)
		written += ft_print_wchar(va_arg(args, wchar_t), conversation);
	else
	{
		i = va_arg(args, int);
		c = (unsigned char)i;
		ft_putchar(c);
		written++;
	}
	if (conversation->flags.left_justified)
		written += ft_print_times(conversation->field_width - 1, ' ');
	return (written);
}
