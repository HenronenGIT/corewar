/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 09:24:31 by hmaronen          #+#    #+#             */
/*   Updated: 2021/11/25 10:42:31 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	convertor(char *str)
{
	int	i;
	int	nb;

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

int	ft_atoi(const char *str)
{
	int		i;
	int		temp;

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
