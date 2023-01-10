/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:22:36 by okoponen          #+#    #+#             */
/*   Updated: 2023/01/10 10:58:00 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
