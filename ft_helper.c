/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatsuk <amatsuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 16:35:32 by amatsuk           #+#    #+#             */
/*   Updated: 2018/03/07 16:44:44 by amatsuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			get_width(t_conversation *conversation,
								t_format *fomat_string, va_list args)
{
	int width;

	width = va_arg(args, int);
	if (width < 0)
	{
		conversation->flags.left_justified = 1;
		width = (-1) * width;
	}
	fomat_string->current_position++;
	return (width);
}

void		get_field_width(t_conversation *conversation,
								t_format *fomat_string, va_list args)
{
	int	width;
	int width2;

	width = 0;
	if (get_current_char(fomat_string) == '*')
		width = get_width(conversation, fomat_string, args);
	if (get_current_char(fomat_string) != '*')
	{
		width2 = ft_atoi(fomat_string->format + fomat_string->current_position);
		while (ft_isdigit(get_current_char(fomat_string)))
			fomat_string->current_position++;
	}
	if (get_current_char(fomat_string) == '*')
		get_field_width(conversation, fomat_string, args);
	else
	{
		width = (width < 0 ? -width : width);
		if (width2)
			width = width2;
		conversation->field_width = width;
	}
}

void		get_precision(t_conversation *conversation,
									t_format *fomat_string, va_list args)
{
	int precision;

	precision = 0;
	conversation->precision = precision;
	if (get_current_char(fomat_string) == '.')
	{
		conversation->precision_exist = 1;
		fomat_string->current_position++;
		if (get_current_char(fomat_string) == '*')
		{
			precision = va_arg(args, int);
			conversation->precision = precision;
			fomat_string->current_position++;
		}
		else
		{
			precision = ft_atoi(fomat_string->format +
				fomat_string->current_position);
			conversation->precision = precision;
			while (ft_isdigit(get_current_char(fomat_string)))
				fomat_string->current_position++;
		}
	}
	else
		conversation->precision_exist = 0;
}

void		get_length_modifier(t_conversation *conversation,
									t_format *fomat_string)
{
	char c;

	conversation->length_modifier = none;
	c = get_current_char(fomat_string);
	while (c != '\0' && (!is_modifier(c)))
	{
		if (c == 'L')
			conversation->length_modifier = L;
		else if (c == 'l' && conversation->length_modifier == l)
			conversation->length_modifier = ll;
		else if (c == 'l' && conversation->length_modifier != ll)
			conversation->length_modifier = l;
		else if (c == 'h' && conversation->length_modifier == h)
			conversation->length_modifier = hh;
		else if (c == 'h' && conversation->length_modifier != hh)
			conversation->length_modifier = h;
		else if (c == 'j')
			conversation->length_modifier = j;
		else if (c == 'z')
			conversation->length_modifier = z;
		else if (c == 'w')
			conversation->length_modifier = w;
		fomat_string->current_position++;
		c = get_current_char(fomat_string);
	}
}

void		get_specifier(t_conversation *conversation,
								t_format *fomat_string, va_list va_arg)
{
	char	c;
	int		f;

	f = 1;
	c = get_current_char(fomat_string);
	while (c != '\0' && is_modifier(c) && f)
	{
		f = 0;
		if (!process_specifier(c, fomat_string, va_arg, conversation))
			f = 1;
		fomat_string->current_position++;
		c = get_current_char(fomat_string);
	}
}
