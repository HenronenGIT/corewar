/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:13:20 by hmaronen          #+#    #+#             */
/*   Updated: 2021/11/30 17:18:08 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_print_array(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_putstr(arr[i]);
		ft_putchar('\n');
		i++;
	}
}
