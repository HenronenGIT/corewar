/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:31:04 by hmaronen          #+#    #+#             */
/*   Updated: 2021/11/17 14:28:24 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;

	i = ft_strlen((char *)str);
	while ((i + 1) != 0)
	{
		if (str[i] == c)
			return ((char *)&str[i]);
		i--;
	}
	if (c == '\0')
		return ((char *)&str[i]);
	return (0);
}
