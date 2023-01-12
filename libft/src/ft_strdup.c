/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:32:45 by hmaronen          #+#    #+#             */
/*   Updated: 2022/01/03 11:36:03 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *str)
{
	char	*cpy;
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	cpy = ft_strnew(i);
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (str[i] != 0)
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
