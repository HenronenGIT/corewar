/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 13:04:06 by hmaronen          #+#    #+#             */
/*   Updated: 2021/12/03 13:30:56 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*converter(int n, char *str, int i)
{
	while (i >= 0 && str[i] != '-')
	{
		str[i] = n % 10 + 48;
		n = n / 10;
		i--;
	}
	return (str);
}

static char	*ft_negative_handler(int i)
{
	char	*str;

	str = ft_strnew(i + 1);
	if (!str)
		return (NULL);
	str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;

	i = ft_digit_counter(n, 10);
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		if (n == -2147483648)
			return (ft_strdup("-2147483648"));
		str = ft_negative_handler(i);
		if (!str)
			return (NULL);
		n = n * -1;
	}
	else
	{
		str = ft_strnew(i);
		if (!str)
			return (NULL);
		i = i - 1;
	}
	return (converter(n, str, i));
}
