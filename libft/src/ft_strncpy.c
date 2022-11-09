/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:40:44 by hmaronen          #+#    #+#             */
/*   Updated: 2021/11/25 10:29:58 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i != len)
	{
		if (src[i] == '\0')
		{
			while (i != len)
			{
				dest[i] = '\0';
				i++;
			}
		}
		else
		{
			dest[i] = src[i];
			i++;
		}
	}
	return (dest);
}
