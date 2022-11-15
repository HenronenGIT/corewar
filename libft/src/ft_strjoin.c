/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:57:13 by hmaronen          #+#    #+#             */
/*   Updated: 2021/11/18 13:36:45 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		len;
	int		i;

	i = 0;
	if (s1 == 0 || s2 == 0)
		return (NULL);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	new_str = ft_strnew(len);
	if (new_str == NULL)
		return (NULL);
	ft_strcpy(new_str, s1);
	ft_strcat(new_str, s2);
	while (new_str[i] != 0)
		i++;
	new_str[i] = '\0';
	return (new_str);
}
