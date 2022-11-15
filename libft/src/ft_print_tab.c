/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 19:25:39 by hmaronen          #+#    #+#             */
/*   Updated: 2022/08/09 19:25:40 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_print_tab(int *tab, size_t tab_size)
{
	size_t	i;

	i = 0;
	while (i < tab_size)
	{
		ft_putnbr(tab[i]);
		ft_putchar('\n');
		i += 1;
	}
	return ;
}
