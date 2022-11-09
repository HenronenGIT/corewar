/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.Hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:34:31 by hmaronen          #+#    #+#             */
/*   Updated: 2022/06/20 16:34:34 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtoupper(char *string)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_strnew(ft_strlen(string));
	while (string[i])
	{
		if (string[i] >= 97 && string[i] <= 122)
			result[i] = (string[i] - 32);
		else
			result[i] = string[i];
		i++;
	}
	ft_strdel(&string);
	return (result);
}
