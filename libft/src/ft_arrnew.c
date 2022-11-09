/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:50:14 by hmaronen          #+#    #+#             */
/*   Updated: 2022/01/24 11:50:16 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	**ft_arrnew(size_t str_count, size_t str_len)
{
	char	**arr;
	int		i;

	i = -1;
	arr = (char **)malloc(sizeof(char *) * (str_count + 1));
	if (!arr)
		return (NULL);
	arr[str_count] = NULL;
	while (++i != (int)str_count)
	{
		arr[i] = ft_strnew(str_len);
		if (!arr[i])
			return (NULL);
		ft_bzero(arr[i], str_len);
	}
	return (arr);
}
