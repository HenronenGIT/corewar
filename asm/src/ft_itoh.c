/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoponen <okoponen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:33:57 by okoponen          #+#    #+#             */
/*   Updated: 2022/11/23 12:33:58 by okoponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char	*ft_itoh(int num, int byte_size)
{
	int		i;
	int		j;
	char	*final;
	char	*temp;

	i = 0;
	j = 0;
	final = (char *)malloc(sizeof(char) * (byte_size * 2 + 1));
	if (!final)
		exit (MALLOC_ERR);
	final[byte_size * 2] = '\0';
	while (i < byte_size * 2)
		final[i++] = '0';
	temp = ft_itoa_base(num, 16);
	i = byte_size * 2 - ft_strlen(temp);
	while (i <= byte_size * 2)
		final[i++] = temp[j++];
	return (final);
}
