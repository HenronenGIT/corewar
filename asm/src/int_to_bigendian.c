/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_to_bigendian.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoponen <okoponen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:49:36 by okoponen          #+#    #+#             */
/*   Updated: 2022/11/30 13:49:41 by okoponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int	int_to_bigendian_4(int value)
{
	int converted;

	converted = 0;
//	printf("Value Before Converting = 0x%x\n", value);
	converted |= ((0x000000ff & value) << 24);
	converted |= ((0x0000ff00 & value) << 8);
	converted |= ((0x00ff0000 & value) >> 8);
	converted |= ((0xff000000 & value) >> 24);
//	printf("Value After Converting = 0x%x\n", converted);
    return (converted);
}

int int_to_bigendian_3(int value)
{
	int converted;

	converted = 0;
//	printf("Value Before Converting = 0x%x\n", value);
	converted |= ((0x0000ff & value) << 16);
	converted |= ((0xff0000 & value) >> 16);
	converted |= (0x00ff00 & value);
//	printf("Value After Converting = 0x%x\n", converted);
	return (converted);
}

int int_to_bigendian_2(int value)
{
	int converted;

	converted = 0;
//	printf("Value Before Converting = 0x%x\n", value);
	converted |= ((0x00ff & value) << 8);
	converted |= ((0xff00 & value) >> 8);
//	printf("Value After Converting = 0x%x\n", converted);
	return (converted);
}

int		int_to_bigendian(int value, int size)
{
	if (size == 2)
		return (int_to_bigendian_2(value));
	else if (size == 3)
		return (int_to_bigendian_3(value));
	else if (size == 4)
		return (int_to_bigendian_4(value));
	else
		return (-1);
}

