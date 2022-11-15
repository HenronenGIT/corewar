/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:15:34 by hmaronen          #+#    #+#             */
/*   Updated: 2022/05/11 16:15:41 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrev(char *str)
{
	char	*rev_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	rev_str = ft_strnew(i);
	while (--i >= 0)
		rev_str[j++] = str[i];
	return (rev_str);
}
