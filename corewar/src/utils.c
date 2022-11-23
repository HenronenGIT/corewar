/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:40:16 by akilk             #+#    #+#             */
/*   Updated: 2022/11/23 15:04:24 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

/*
** Check if champion's filename is ending with extension .cor
*/

bool	is_cor_file(char *file)
{
	if ( ft_strlen(file) >= 4 && !ft_strcmp(ft_strchr(file, '\0') - ft_strlen(".cor"), ".cor"))
		return (true);
	else
		return (false);
}

/*
** Converting bytes to signed integer using bitwise operators.
** If signed bit is 1, apply masking.
*/

/*
  Bitwise    Logical
+----------+---------+
|  a & b   |  a && b |
+----------+---------+
| a ^ b    |  a != b |
+----------+---------+
|    ~a    |   !a    |
+----------+---------+
*/

int32_t	bytes2int(uint8_t *byte_value, size_t size)
{
	int		signbit;
	int		n;
	int32_t	decimal;

	decimal = 0;
	signbit = 0;
	if (byte_value[0] & 0x80)
		signbit = 1;
	n = 0;
	while (size)
	{
		if (signbit)
			decimal += ((byte_value[size - 1] ^ 0xFF) << (n * 8));
		else
			decimal += byte_value[size - 1] << (n * 8);
		n++;
		size--;
	}
	if (signbit)
		decimal = ~(decimal);
	return (decimal);
}

void	print_data(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < MEM_SIZE)
	{
		j = 0;
		while (j < 32)
		{
			ft_printf("%.2x ", (uint8_t)data->arena[i]);
			i++;
			j++;
		}
		ft_printf("\n");
	}
	exit (0);
}
