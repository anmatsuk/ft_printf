/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatsuk <amatsuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 15:57:09 by amatsuk           #+#    #+#             */
/*   Updated: 2018/03/08 14:44:08 by amatsuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_putbignbr(long long nb)
{
	if (nb >= 10 || nb <= -10)
	{
		ft_putbignbr(nb / 10);
		if (nb < 0)
			ft_putchar(-(nb % 10) + '0');
		else
			ft_putchar(nb % 10 + '0');
	}
	else
	{
		if (nb < 0)
			ft_putchar(-(nb % 10) + '0');
		else
			ft_putchar(nb % 10 + '0');
	}
}

void		ft_putbiglnbr(unsigned long long nb)
{
	if (nb >= 10)
	{
		ft_putbignbr(nb / 10);
		ft_putchar(nb % 10 + '0');
	}
	else
		ft_putchar(nb % 10 + '0');
}

int			ft_print_times(int field_width, char time)
{
	int	i;

	i = 0;
	while (i < field_width)
	{
		ft_putchar(time);
		i++;
	}
	return (i);
}

int			get_integer_size(long long value)
{
	long long	i;
	int			sign;
	int			len;

	sign = 0;
	i = value;
	len = 0;
	if (value < 0)
	{
		sign = 1;
	}
	while (i >= 10 || i <= -10)
	{
		i = i / 10;
		len++;
	}
	len++;
	return (sign + len);
}

int			get_linteger_size(unsigned long long value)
{
	unsigned long long	i;
	int					len;

	i = value;
	len = 0;
	while (i >= 10)
	{
		i = i / 10;
		len++;
	}
	len++;
	return (len);
}
