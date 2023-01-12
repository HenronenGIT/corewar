/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.Hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 14:05:15 by hmaronen          #+#    #+#             */
/*   Updated: 2021/12/27 14:05:17 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_realloc(char **s1, char const *s2)
{
	size_t	len;
	char	*temp;

	if (s2 == NULL)
		return ;
	if (*s1 == NULL)
	{
		*s1 = (char *)s2;
		return ;
	}

	len = ft_strlen((char *)*s1) + ft_strlen((char *)s2);
	temp = ft_strdup(*s1);
	if (temp == NULL)
		return ;
	ft_memdel((void **)s1);
	*s1 = ft_strnew(len);
	ft_strcpy(*s1, temp);
	ft_memdel((void **)&temp);
	ft_strcat(*s1, s2);
}
