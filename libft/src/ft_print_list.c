/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.Hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:31:29 by hmaronen          #+#    #+#             */
/*   Updated: 2021/11/26 14:10:15 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_print_list(t_list *list)
{
	while (list)
	{
		ft_putstr(list->content);
		list = list->next;
		ft_putchar('\n');
	}
}
