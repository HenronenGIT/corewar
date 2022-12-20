/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:40:16 by akilk             #+#    #+#             */
/*   Updated: 2022/12/16 10:28:56 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Check if champion's filename is ending with extension .cor
*/

bool	is_cor_file(char *file)
{
	if (ft_strlen(file) >= 4 \
	&& !ft_strcmp(ft_strchr(file, '\0') - ft_strlen(".cor"), ".cor"))
		return (true);
	else
		return (false);
}

bool	valid_int(char *str)
{
	int		i;
	double	num;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	num = ft_atol(str);
	if (num < 0 || num > INT_MAX)
		return (false);
	return (true);
}

/*
** Converting bytes to signed integer using bitwise operators.
** If signed bit is 1, apply masking.
*/

int32_t	bytes2int(uint8_t *byte_value, int start, size_t size)
{
	int		signbit;
	int		n;
	int32_t	decimal;
	int		idx;

	decimal = 0;
	signbit = 0;
	if (byte_value[start] & 0x80)
		signbit = 1;
	n = 0;
	while (size)
	{
		idx = (start + (size - 1)) % MEM_SIZE;
		if (signbit)
			decimal += ((byte_value[idx] ^ 0xFF) << (n * 8));
		else
			decimal += byte_value[idx] << (n * 8);
		n++;
		size--;
	}
	if (signbit)
		decimal = ~(decimal);
	return (decimal);
}
