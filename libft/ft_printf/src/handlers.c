/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:57:51 by hmaronen          #+#    #+#             */
/*   Updated: 2022/05/10 16:57:53 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	c_handler(t_flags *flag)
{
	char	ch;

	ch = va_arg(flag->args, int);
	flag->ret_len += 1;
	if (flag->width && !flag->minus)
		flag->ret_len += put_padding((flag->width - 1), ' ');
	ft_putchar(ch);
	if (flag->width && flag->minus)
		flag->ret_len += put_padding((flag->width - 1), ' ');
}

void	s_handler(t_flags *flag)
{
	char	*arg_str;
	int		malloc;

	malloc = 0;
	arg_str = va_arg(flag->args, char *);
	if (flag->precision || !arg_str)
	{
		if (!arg_str)
		{
			if (flag->precision)
				arg_str = ft_strndup("(null)", flag->prec_len - 1);
			else
				arg_str = ft_strdup("(null)");
		}
		else
			arg_str = ft_strsub(arg_str, 0, flag->prec_len);
		malloc = 1;
	}
	flag->precision = 0;
	flag->prec_len = 0;
	flag->arg_len = ft_strlen(arg_str);
	nb_padding(flag, arg_str, "");
	if (malloc)
		free(arg_str);
}

void	x_handler(t_flags *flag)
{
	unsigned long	arg;
	char			*arg_str;
	char			*prefix;

	prefix = NULL;
	arg = 0;
	arg = va_arg(flag->args, unsigned long);
	unsigned_length_modifiers(flag, &arg);
	arg_str = ft_unsigned_itoa_base(arg, 16);
	if (flag->precision && flag->prec_len == 0)
		ft_strdel(&arg_str);
	flag->arg_len = ft_strlen(arg_str);
	if (flag->hash && arg_str && *arg_str != '0')
	{
		flag->ret_len += 2;
		prefix = ft_strdup("0x");
	}
	nb_padding(flag, arg_str, prefix);
	free(arg_str);
	free(prefix);
}

void	big_x_handler(t_flags *flag)
{
	unsigned long	arg;
	char			*arg_str;
	char			*prefix;

	prefix = NULL;
	arg = 0;
	arg = va_arg(flag->args, unsigned long);
	unsigned_length_modifiers(flag, &arg);
	arg_str = ft_strtoupper(ft_unsigned_itoa_base(arg, 16));
	if (flag->precision && flag->prec_len == 0)
		ft_strdel(&arg_str);
	flag->arg_len = ft_strlen(arg_str);
	if (flag->hash && arg_str && *arg_str != '0')
	{
		flag->ret_len += 2;
		prefix = ft_strdup("0X");
	}
	nb_padding(flag, arg_str, prefix);
	ft_strdel(&arg_str);
	ft_strdel(&prefix);
}

void	di_handler(t_flags *flag)
{
	char	*str;
	long	arg;

	arg = 0;
	arg = va_arg(flag->args, long);
	length_modifiers(flag, &arg);
	if (arg < 0 && arg != LONG_MIN)
	{
		arg *= -1;
		flag->is_neg = 1;
	}
	str = ft_itoa_base(arg, 10);
	if (flag->precision && flag->prec_len == 0 && *str == '0')
	{
		free(str);
		str = NULL;
	}
	else
		flag->arg_len = ft_strlen(str);
	nb_padding(flag, str, "");
	free(str);
}
