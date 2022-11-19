/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 11:24:17 by hmaronen          #+#    #+#             */
/*   Updated: 2021/11/18 10:22:27 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	int	i;

	i = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != 0 && s2[i] != 0)
		i++;
	if (s1[i] == s2[i])
		return (1);
	else
		return (0);
}
