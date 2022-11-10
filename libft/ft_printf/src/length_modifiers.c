/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_modifiers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:34:28 by hmaronen          #+#    #+#             */
/*   Updated: 2022/05/24 15:34:29 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	length_modifiers(t_flags *flag, long *number_ptr)
{
	if (flag->h)
		*number_ptr = (short)*number_ptr;
	else if (flag->hh)
		*number_ptr = (char)*number_ptr;
	else if (flag->l)
		*number_ptr = (long)*number_ptr;
	else if (flag->ll)
		*number_ptr = (long long)*number_ptr;
	else
		*number_ptr = (int)*number_ptr;
}

void	unsigned_length_modifiers(t_flags *flag, unsigned long *number_ptr)
{
	if (flag->h)
		*number_ptr = (unsigned short)*number_ptr;
	else if (flag->hh)
		*number_ptr = (unsigned char)*number_ptr;
	else if (flag->l)
		*number_ptr = (unsigned long)*number_ptr;
	else if (flag->ll)
		*number_ptr = (unsigned long long)*number_ptr;
	else
		*number_ptr = (unsigned int)*number_ptr;
}

long double	double_length_modifiers(t_flags *flag)
{
	if (flag->l)
		return (va_arg(flag->args, double));
	else if (flag->ll)
		return (va_arg(flag->args, long double));
	else
		return (va_arg(flag->args, double));
}
