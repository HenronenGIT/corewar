/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.Hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 12:51:17 by hmaronen          #+#    #+#             */
/*   Updated: 2022/07/15 12:51:21 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static long	convertor(char *str)
{
	long	i;
	long	nb;

	nb = 0;
	i = 0;
	while (str[i] != 0)
	{
		if (!ft_isdigit(str[i]))
			return (nb);
		nb = (nb * 10) + str[i] - 48;
		i++;
	}
	return (nb);
}

long	ft_atol(const char *str)
{
	long	i;
	long	temp;

	temp = 1;
	i = 0;
	if (ft_isalpha(str[i]))
		return (0);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' && str[i + 1] == '+'
		&& str[i] == '-' && str[i + 1] == '-')
		return (0);
	if (str[i] == '-')
	{
		temp = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	return (convertor((char *)&str[i]) * temp);
}
