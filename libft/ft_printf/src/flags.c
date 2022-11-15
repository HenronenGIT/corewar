/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.Hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 21:35:34 by hmaronen          #+#    #+#             */
/*   Updated: 2022/06/28 21:35:37 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_length_modifiers(t_flags *flag, const char *str, char specif)
{
	while (*str != specif)
	{
		if (*str == 'h' && flag->h)
		{
			flag->h = 0;
			flag->hh = 1;
		}
		if (*str == 'h' && !flag->hh)
			flag->h = 1;
		if ((*str == 'l' && flag->l) || *str == 'L')
		{
			flag->l = 0;
			flag->ll = 1;
		}
		if ((*str == 'l') && !flag->ll)
			flag->l = 1;
		str++;
	}
}

void	parse_precision(const char **str, t_flags *flag, char specifier)
{
	while (**str != specifier)
	{
		flag->prec_len = ((10 * flag->prec_len) + **str - 48);
		if (flag->prec_len < 0)
			flag->precision = 0;
		(*str)++;
	}
	(*str)--;
}

void	check_flags(t_flags *flag, const char *str, char specifier)
{
	while (*str != specifier)
	{
		if (*str == '#')
			flag->hash = 1;
		if (*str == '0' && !flag->width && !flag->minus)
			flag->zero = 1;
		if (*str == '-')
			flag->minus = 1;
		if (*str == '+')
			flag->plus = 1;
		if (*str == '.')
			flag->precision = 1;
		if (*str == ' ')
			flag->space = 1;
		if (ft_isdigit(*str) && !flag->precision)
			flag->width = ((10 * flag->width) + *str - 48);
		else if (ft_isdigit(*str))
			parse_precision(&str, flag, specifier);
		str++;
	}
	if (flag->space && flag->plus)
		flag->space = 0;
	if (flag->zero && flag->minus)
		flag->zero = 0;
}
