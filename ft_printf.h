/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatsuk <amatsuk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 15:34:41 by amatsuk           #+#    #+#             */
/*   Updated: 2018/03/08 18:56:01 by amatsuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <stddef.h>
# include "libft.h"

typedef enum			e_length_modifier
{
	none, hh, h, l, ll, j, z, t, L, w
}						t_length_modifier;

typedef enum			e_specifier
{
	s, S, d, o, x, X, u, U, f, e, a, g, n, p, c, err
}						t_specifier;

typedef	struct			s_flags
{
	short				left_justified;
	short				sign;
	short				space;
	short				alternative;
	short				zeros;
}						t_flags;

typedef struct			s_conversation
{
	t_specifier			specifier;
	t_length_modifier	length_modifier;
	t_flags				flags;
	int					field_width;
	int					precision;
	int					precision_exist;
	int					warrning;
	char				*comment;

}						t_conversation;

typedef	struct			s_format
{
	char				*format;
	size_t				current_position;
	unsigned long		written;
	char				buffer[256];
	int					buf_position;
}						t_format;

int						ft_printf(const char *format, ...);
int						print_argument(t_format *fomat_string, va_list args);
int						ft_print_wchar(wchar_t c, t_conversation *cc);
int						ft_print_times(int field_width, char time);
int						ft_print_char(t_conversation *conversation,
										va_list args);
int						ft_print_string(t_conversation *conversation,
										va_list args, char c);
int						process_integer(t_conversation *conversation,
										va_list args, char c);
void					ft_putbignbr(long long nb);
void					ft_putbiglnbr(unsigned long long nb);
int						get_integer_size(long long value);
int						get_linteger_size(unsigned long long value);
void					handle_flags(t_conversation *conversation, int len,
										long long value);
unsigned long long int	convert_uinteger(unsigned long long int value,
										t_conversation *conversation);
int						process_linteger(t_conversation *conversation,
										va_list args, char c);
int						process_octal_hex(t_conversation *conversation,
										va_list args, char c);
int						ft_process_pointer(t_conversation *conversation,
											va_list args);
char					*itoa_base(unsigned long long value, int base,
								t_conversation *conversation);
void					handle_octal_flags(t_conversation *conversation,
									int len, long long value);
long long				convert_integer(long long value,
										t_conversation *conversation);
int						process_specifier(char c, t_format *fomat_string,
							va_list va_arg, t_conversation *conversation);
int						print_persent(t_conversation *conversation);
int						is_flag(char c);
int						is_modifier(char c);
char					get_current_char(t_format *fomat_string);
void					get_precision(t_conversation *conversation,
										t_format *fomat_string, va_list args);
void					get_length_modifier(t_conversation *conversation,
											t_format *fomat_string);
void					get_specifier(t_conversation *conversation,
									t_format *fomat_string, va_list va_arg);
void					get_field_width(t_conversation *conversation,
										t_format *fomat_string, va_list args);
void					gather_flags(t_conversation *conversation,
										t_format *fomat_string);

#endif
