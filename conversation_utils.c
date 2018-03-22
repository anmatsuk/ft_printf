/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatsuk <amatsuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 16:35:32 by amatsuk           #+#    #+#             */
/*   Updated: 2018/03/22 12:09:47 by amatsuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		get_current_char(t_format *fomat_string)
{
	return (*(fomat_string->format + fomat_string->current_position));
}

int			is_flag(char c)
{
	if (c == '-' || c == '+' || c == '#' || c == ' ' || c == '0')
		return (1);
	return (0);
}

int			is_modifier(char c)
{
	if (c == 'c' || c == 'C' || c == 's' || c == 'S' || c == 'd'
		|| c == 'x' || c == 'X' || c == 'u' || c == 'F' || c == 'p'
		|| c == 'f' || c == 'e' || c == 'E' || c == 'a' || c == 'D'
		|| c == 'A' || c == 'g' || c == 'G' || c == 'n' || c == 'i'
		|| c == 'p' || c == 'U' || c == 'o' || c == 'O' || c == '%')
		return (1);
	return (0);
}

int			process_specifier(char c, t_format *fomat_string,
								va_list va_arg, t_conversation *conversation)
{
	if (c == 'c' || c == 'C')
		fomat_string->written += ft_print_char(conversation, va_arg);
	else if (c == 's' || c == 'S')
		fomat_string->written += ft_print_string(conversation, va_arg, c);
	else if (c == 'd' || c == 'i' || c == 'D')
		fomat_string->written += process_integer(conversation, va_arg, c);
	else if (c == 'x' || c == 'X' || c == 'o' || c == 'O')
		fomat_string->written += process_octal_hex(conversation, va_arg, c);
	else if (c == 'u' || c == 'U')
		fomat_string->written += process_linteger(conversation, va_arg, c);
	else if (c == 'p')
		fomat_string->written += ft_process_pointer(conversation, va_arg);
	else if (c == '%')
		fomat_string->written += print_persent(conversation);
	else
		return (0);
	return (1);
}

int			print_persent(t_conversation *conversation)
{
	int written;

	written = 0;
	if (!conversation->flags.left_justified)
		written += ft_print_times(conversation->field_width - 1, ' ');
	ft_putchar('%');
	if (conversation->flags.left_justified)
		written += ft_print_times(conversation->field_width - 1, ' ');
	return (written + 1);
}
