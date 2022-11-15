/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:11:58 by hmaronen          #+#    #+#             */
/*   Updated: 2021/11/29 11:26:21 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* Applies the function f to each character of the string given
* as argument to create a “fresh” new string (with malloc(3))
* resulting from the successive applications of f */

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*str;

	i = 0;
	if (s == NULL)
		return (NULL);
	str = ft_strnew(ft_strlen((char *)s));
	if (str != 0)
	{
		while (s[i] != 0)
		{
			str[i] = f(s[i]);
			i++;
		}
	}
	return (str);
}
