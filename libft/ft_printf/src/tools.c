/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:26:28 by hmaronen          #+#    #+#             */
/*   Updated: 2022/05/11 14:26:39 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	put_ptr(uintptr_t addr)
{
	if (addr >= 16)
	{
		put_ptr(addr / 16);
		put_ptr(addr % 16);
	}
	else
	{
		if (addr < 10)
			ft_putchar(addr + 48);
		else
			ft_putchar(addr + 87);
	}
}

int	put_padding(int width, char ch)
{
	int	i;

	i = -1;
	while (++i < width)
		ft_putchar(ch);
	return (i);
}
