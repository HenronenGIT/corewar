/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:08:09 by hmaronen          #+#    #+#             */
/*   Updated: 2021/11/12 16:40:55 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem_area;

	mem_area = (void *)malloc(size);
	if (mem_area == NULL)
		return (NULL);
	else
		ft_memset(mem_area, 0, size);
	return (mem_area);
}
