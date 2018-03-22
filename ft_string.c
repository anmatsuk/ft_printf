/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatsuk <amatsuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 18:44:56 by amatsuk           #+#    #+#             */
/*   Updated: 2018/03/07 18:53:53 by amatsuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_wstrlen(wchar_t *str)
{
	size_t len;

	len = 0;
	while (*str != '\0')
	{
		str++;
		len++;
	}
	return (len);
}

static int	ft_print_wstring(t_conversation *conversation, va_list args)
{
	wchar_t *wstr;
	int		written;
	int		width;
	int		len;

	written = 0;
	wstr = va_arg(args, wchar_t*);
	if (!wstr)
		wstr = L"(null)";
	len = ft_wstrlen(wstr);
	width = len;
	if (conversation->precision_exist)
		width = (len < conversation->precision ? len : conversation->precision);
	if (!conversation->flags.left_justified)
		written += ft_print_times((conversation->field_width - width), ' ');
	len = width;
	while (--len >= 0)
	{
		ft_print_wchar(*wstr, conversation);
		wstr++;
		written++;
	}
	if (conversation->flags.left_justified)
		written += ft_print_times((conversation->field_width - width), ' ');
	return (written);
}

static int	process_string(t_conversation *conversation, va_list args)
{
	char	*str;
	int		written;
	int		len;

	written = 0;
	str = va_arg(args, char*);
	if (!str)
		str = "(null)";
	len = (int)ft_strlen(str);
	if (conversation->precision_exist)
		len = (len < conversation->precision ? len : conversation->precision);
	if (!conversation->flags.left_justified)
		written += ft_print_times((conversation->field_width - len), ' ');
	write(1, str, len);
	written += len;
	if (conversation->flags.left_justified)
		written += ft_print_times((conversation->field_width - len), ' ');
	return (written);
}

int			ft_print_string(t_conversation *conversation, va_list args, char c)
{
	conversation->specifier = (c == 's' ? s : S);
	if (conversation->precision < 0)
		conversation->precision_exist = 0;
	if (conversation->length_modifier == w || c == 'S'
		|| conversation->length_modifier == l)
		return (ft_print_wstring(conversation, args));
	else
		return (process_string(conversation, args));
}
