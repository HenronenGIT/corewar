/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_translator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoponen <okoponen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:23:23 by okoponen          #+#    #+#             */
/*   Updated: 2022/11/24 11:23:24 by okoponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	hex_translator(char *str, int fd, int len)
{
	int		i;
	char	*temp;

	temp = NULL;
	i = 0;
	while (str[i])
	{
		temp = ft_itoh((int)str[i], 1);
		write(fd, temp, 2);
		i++;
		free(temp);
	}
	while (i < len)
	{
		write(fd, "00", 2);
		i++;
	}
}
