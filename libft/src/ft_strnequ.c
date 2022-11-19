/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:24:33 by hmaronen          #+#    #+#             */
/*   Updated: 2021/11/18 10:48:31 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s1 == 0 || s2 == 0 || n == 0)
		return (1);
	while (s1[i] == s2[i] && s1[i] != 0 && s2[i] != 0 && i < (n - 1))
		i++;
	if (s1[i] == s2[i])
		return (1);
	else
		return (0);
}
