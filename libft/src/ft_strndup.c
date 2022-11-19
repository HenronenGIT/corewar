/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.Hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 17:52:32 by hmaronen          #+#    #+#             */
/*   Updated: 2021/12/21 17:53:11 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strndup(const char *str, size_t n)
{
	char	*cpy;
	size_t	i;

	i = 0;
	cpy = ft_strnew(ft_strlen(str));
	if (cpy == NULL)
		return (NULL);
	while (i <= n && str[i] != '\0')
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
