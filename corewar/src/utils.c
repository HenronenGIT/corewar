/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:40:16 by akilk             #+#    #+#             */
/*   Updated: 2022/12/05 15:52:32 by wdonnell         ###   ########.fr       */
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

bool	valid_int(char *str)
{
	int	i;
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

	i = 1;
	while (i <= MEM_SIZE)
	{
		ft_printf("%.2x", (uint8_t)data->arena[i - 1]);
		if (i % 32 == 0)
			ft_printf("\n");
		else
			ft_printf(" ");
		i++;
	}
	exit (0);
}

void	print_contestants(t_data *data)
{
	int	i;

	i = 1;
	ft_printf("Introducing contestants...\n");
	while (i <= data->champions_num)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",\
			i, data->champions[i - 1]->code_size, data->champions[i - 1]->name,\
			data->champions[i - 1]->comment);
		i++;
	}
}

void	print_last_alive(t_data *data)
{
	int	i;

	i = data->last_alive_champ;
	ft_printf("Contestant %d, \"%s\", has won !\n", i, data->champions[i - 1]->name);
}