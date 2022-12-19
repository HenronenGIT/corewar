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
	int		temp;

	temp = 0;
	i = 0;
	while (i < len)
	{
		if (str[i])
			temp = (int)str[i];
		else
			temp = 0;
		write(fd, &temp, 1);
		i++;
	}
}
