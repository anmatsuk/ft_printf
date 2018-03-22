/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatsuk <amatsuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:34:41 by amatsuk           #+#    #+#             */
/*   Updated: 2018/03/08 18:56:01 by amatsuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			gather_flags(t_conversation *conversation,
								t_format *fomat_string)
{
	char	c;

	c = get_current_char(fomat_string);
	while (c != '\0' && is_flag(c))
	{
		if (c == '-')
			conversation->flags.left_justified = 1;
		else if (c == '+')
			conversation->flags.sign = 1;
		else if (c == '#')
			conversation->flags.alternative = 1;
		else if (c == ' ')
			conversation->flags.space = 1;
		else if (c == '0')
			conversation->flags.zeros = 1;
		fomat_string->current_position++;
		c = get_current_char(fomat_string);
	}
}

int				print_argument(t_format *fomat_string, va_list args)
{
	t_conversation	conversation;

	conversation.specifier = err;
	conversation.warrning = 0;
	conversation.flags.left_justified = 0;
	conversation.flags.sign = 0;
	conversation.flags.space = 0;
	conversation.flags.alternative = 0;
	conversation.flags.zeros = 0;
	gather_flags(&conversation, fomat_string);
	get_field_width(&conversation, fomat_string, args);
	get_precision(&conversation, fomat_string, args);
	get_length_modifier(&conversation, fomat_string);
	get_specifier(&conversation, fomat_string, args);
	return (0);
}

static int		make_conversation(char *format, va_list args)
{
	int			i;
	t_format	fmt;

	i = 0;
	fmt.format = format;
	fmt.written = 0;
	fmt.current_position = 0;
	fmt.buf_position = 0;
	while (*(format + fmt.current_position) != '\0')
	{
		if (*(format + fmt.current_position) == '%')
		{
			fmt.current_position++;
			print_argument(&fmt, args);
		}
		else
		{
			ft_putchar(*(format + fmt.current_position));
			fmt.written++;
			fmt.current_position++;
		}
	}
	return (fmt.written);
}

int				ft_printf(const char *format, ...)
{
	char	*format_string;
	va_list	args;
	int		count;

	if (!format)
	{
		ft_putstr("error: too few arguments to function call");
		exit(1);
	}
	format_string = (char*)format;
	va_start(args, format);
	count = make_conversation(format_string, args);
	va_end(args);
	return (count);
}
