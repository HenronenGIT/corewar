/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoponen <okoponen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:22:36 by okoponen          #+#    #+#             */
/*   Updated: 2022/11/22 13:22:42 by okoponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int	ft_btoi(char *num)
{
	int	integer;
	int	i;
	int	bitvalue;
	int	len;

	bitvalue = 2;
	integer = 0;
	len = ft_strlen(num) - 2;
	i = 0;
	while (len--)
		bitvalue = bitvalue * 2;
	while (num[i])
	{
		if (num[i] == '1')
			integer += bitvalue;
		i++;
		bitvalue = bitvalue / 2;
	}
	return (integer);
}
