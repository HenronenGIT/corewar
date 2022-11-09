/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:50:54 by hmaronen          #+#    #+#             */
/*   Updated: 2021/11/23 13:18:05 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int			i;
	int			j;
	const char	*sub_string;

	i = 0;
	if (needle[i] == 0)
		return ((char *)haystack);
	while (haystack[i] != 0)
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			sub_string = &haystack[i];
			while (haystack[i + j] == needle[j])
			{
				j++;
				if (needle[j] == 0)
					return ((char *)sub_string);
			}
		}
		i++;
	}
	return (NULL);
}
