/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr_in_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.Hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 16:05:10 by hmaronen          #+#    #+#             */
/*   Updated: 2022/07/15 16:05:11 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_nbr_in_array(int number, int *array, int array_size)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (0);
	while (i < array_size)
	{
		if (number == array[i])
			return (1);
		i += 1;
	}
	return (0);
}
