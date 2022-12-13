/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:28:52 by hmaronen          #+#    #+#             */
/*   Updated: 2022/12/04 11:07:32 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (dst == 0 && src == 0)s
		return (0);
	i = 0;
	while (i != n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return ((void *)dst);
}
*/

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*pd;
	char	*ps;

	//if (!dst && !src && n > 0)
	if (!dst && !src)
		return (NULL);
	pd = (char *)dst;
	ps = (char *)src;
	while (n--)
		*pd++ = *ps++;
	return (dst);
}