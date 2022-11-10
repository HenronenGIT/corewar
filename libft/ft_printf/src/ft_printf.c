/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:49:18 by hmaronen          #+#    #+#             */
/*   Updated: 2022/05/09 10:49:19 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_format(char ch)
{
	if (ch == 'c' || ch == 's' || ch == 'p' || ch == 'x' || ch == 'X'
		|| ch == 'd' || ch == 'i' || ch == 'u' || ch == 'o' || ch == '%'
		|| ch == 'f')
		return (1);
	return (0);
}

static void	init_flag(t_flags *flag)
{
	flag->width = 0;
	flag->space = 0;
	flag->zero = 0;
	flag->plus = 0;
	flag->minus = 0;
	flag->hash = 0;
	flag->precision = 0;
	flag->prec_len = 0;
	flag->arg_len = 0;
	flag->is_neg = 0;
	flag->hh = 0;
	flag->h = 0;
	flag->l = 0;
	flag->ll = 0;
	flag->is_float = 0;
}

static void	jump_table(t_flags *flag, int index)
{
	static t_handler_func	*jump_table[11] = {
		c_handler,
		s_handler,
		p_handler,
		di_handler,
		di_handler,
		o_handler,
		u_handler,
		x_handler,
		big_x_handler,
		f_handler,
		percent_handler
	};

	jump_table[index](flag);
}

const char	*check_format(const char *str, t_flags *flag)
{
	const char	*ptr;
	char		*specifier_ptr;

	ptr = str;
	while (*str != '\0' && !is_format(*str))
		str++;
	if (*str == '\0')
	{
		flag->ret_len += write(1, &(*ptr), 1);
		return (ptr);
	}
	check_flags(flag, ptr, *str);
	check_length_modifiers(flag, ptr, *str);
	specifier_ptr = ft_strchr(FORMATS, *str);
	if (specifier_ptr)
		jump_table(flag, (int)(specifier_ptr - FORMATS));
	return (str);
}

int	ft_printf(const char *format, ...)
{
	t_flags	flag;

	va_start(flag.args, format);
	flag.ret_len = 0;
	while (*format != '\0')
	{
		if (*format != '%')
		{
			ft_putchar(*format);
			flag.ret_len += 1;
		}
		else
		{
			init_flag(&flag);
			format++;
			format = check_format(format, &flag);
		}
		format++;
	}
	va_end(flag.args);
	return (flag.ret_len);
}
