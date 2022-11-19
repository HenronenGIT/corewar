/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.Hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 22:11:37 by hmaronen          #+#    #+#             */
/*   Updated: 2022/05/19 22:11:39 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_sign(t_flags *flag)
{
	if (flag->is_neg)
		flag->ret_len += write(1, "-", 1);
	else if (flag->space)
		flag->ret_len += write(1, " ", 1);
	else
		flag->ret_len += write(1, "+", 1);
	flag->width -= 1;
}

int	count_padding(t_flags *flag, char *prefix, int prec_len)
{
	int	padding_len;
	int	prefix_len;

	padding_len = 0;
	prefix_len = ft_strlen(prefix);
	padding_len = flag->width - flag->arg_len - prec_len;
	if (flag->hash)
		padding_len -= prefix_len;
	if (flag->is_neg || flag->plus || flag->space)
		padding_len -= 1;
	if (padding_len < 0)
		padding_len = 0;
	return (padding_len);
}

int	count_precision(t_flags *flag)
{
	int	prec_padding;

	prec_padding = 0;
	prec_padding = flag->prec_len - flag->arg_len;
	if (prec_padding < 0)
		prec_padding = 0;
	return (prec_padding);
}

/* If statements in order:
	Width
	'.' && '0'
	Sign
	'0' && '.' FOR precision
	' ' && '0'
	#
	'.'
	'0'
	'-'
*/
void	nb_padding(t_flags *flag, char *argument, char *prefix)
{
	int	padding_len;
	int	prec_len;

	flag->ret_len += flag->arg_len;
	prec_len = count_precision(flag);
	padding_len = count_padding(flag, prefix, prec_len);
	if ((flag->space || flag->width) && !flag->zero && !flag->minus)
		flag->ret_len += put_padding(padding_len, ' ');
	if (flag->zero && flag->precision && padding_len >= 0 && !flag->is_float)
		flag->ret_len += put_padding(padding_len, ' ');
	if (flag->plus || flag->is_neg || flag->space)
		put_sign(flag);
	if (flag->zero && flag->precision && flag->is_float)
		flag->ret_len += put_padding(padding_len, '0');
	if (flag->space && flag->zero && !flag->precision)
		flag->ret_len += put_padding(padding_len, '0');
	if (flag->hash)
		ft_putstr(prefix);
	if (flag->precision && padding_len >= 0)
		flag->ret_len += put_padding(prec_len, '0');
	if (flag->zero && !flag->precision && !flag->space)
		flag->ret_len += put_padding((padding_len), '0');
	ft_putstr(argument);
	if (flag->minus && padding_len >= 0)
		flag->ret_len += put_padding(padding_len, ' ');
}
