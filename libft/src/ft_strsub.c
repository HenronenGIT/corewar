/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:53:37 by hmaronen          #+#    #+#             */
/*   Updated: 2021/11/25 10:40:08 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*new_str;
	unsigned int	size;
	unsigned int	i;

	i = 0;
	size = (unsigned int)len;
	if (!s)
		return (NULL);
	new_str = ft_strnew(len);
	if (new_str == NULL)
		return (NULL);
	while (i != size && s[i])
	{
		new_str[i] = s[start];
		start++;
		i++;
	}
	return (new_str);
}
