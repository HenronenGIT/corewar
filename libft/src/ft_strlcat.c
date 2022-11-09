/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:12:44 by hmaronen          #+#    #+#             */
/*   Updated: 2021/11/24 10:25:45 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	d_len;
	size_t	s_len;
	size_t	i;
	size_t	len;

	i = 0;
	d_len = ft_strlen(dest);
	s_len = ft_strlen(((char *)src));
	if (dstsize > d_len)
		len = d_len + s_len;
	else
		len = dstsize + s_len;
	while (src[i] != 0 && (d_len + 1) < dstsize)
	{
		dest[d_len] = src[i];
		i++;
		d_len++;
	}
	dest[d_len] = '\0';
	return (len);
}
