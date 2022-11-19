/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.Hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 22:00:08 by hmaronen          #+#    #+#             */
/*   Updated: 2022/07/06 22:00:09 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	p_handler(t_flags *flag)
{
	unsigned long	argument;
	char			*arg_str;	

	flag->hash = 1;
	flag->ret_len += 2;
	argument = va_arg(flag->args, unsigned long long);
	arg_str = ft_unsigned_itoa_base(argument, 16);
	if (flag->precision && flag->prec_len == 0)
		ft_strdel(&arg_str);
	flag->arg_len += ft_strlen(arg_str);
	nb_padding(flag, arg_str, "0x");
	free(arg_str);
}

void	o_handler(t_flags *flag)
{
	char			*arg_str;
	char			*prefix;
	unsigned long	arg;

	prefix = NULL;
	arg = 0;
	arg = va_arg(flag->args, unsigned long);
	unsigned_length_modifiers(flag, &arg);
	arg_str = ft_unsigned_itoa_base(arg, 8);
	if ((flag->hash && !flag->precision)
		|| (flag->hash && flag->prec_len == 0 && arg == 0)
		|| (flag->hash && flag->prec_len <= (int)ft_strlen(arg_str)))
	{
		flag->ret_len += 1;
		prefix = ft_strdup("0");
	}
	if ((flag->precision && flag->prec_len == 0 && *arg_str == '0')
		|| (flag->hash && *arg_str == '0'))
		ft_strdel(&arg_str);
	flag->arg_len += ft_strlen(arg_str);
	nb_padding(flag, arg_str, prefix);
	free(arg_str);
	free(prefix);
}

void	u_handler(t_flags *flag)
{
	unsigned long	arg;
	char			*str;

	str = NULL;
	arg = 0;
	arg = va_arg(flag->args, unsigned long);
	unsigned_length_modifiers(flag, &arg);
	if (arg < 0)
	{
		arg *= -1;
		flag->is_neg = 1;
	}
	if (flag->precision && flag->prec_len == 0 && arg == 0)
		ft_strdel(&str);
	else
		str = ft_unsigned_itoa_base(arg, 10);
	flag->arg_len = ft_strlen(str);
	nb_padding(flag, str, "");
	ft_strdel(&str);
}

void	percent_handler(t_flags *flag)
{
	flag->precision = 0;
	flag->space = 0;
	flag->arg_len += 1;
	nb_padding(flag, "%", "");
}
