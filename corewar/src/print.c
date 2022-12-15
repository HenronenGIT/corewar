/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 21:49:01 by wdonnell          #+#    #+#             */
/*   Updated: 2022/12/15 14:43:14 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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

void	print_orig_data(t_data *data)
{
	int				i;
	unsigned int	n;

	n = 64;
	i = 1;
	ft_printf("0x%.4x : ", 0);
	while (i <= MEM_SIZE)
	{
		ft_printf("%.2x ", (uint8_t)data->arena[i - 1]);
		if (i % 64 == 0)
		{
			ft_printf("\n");
			if (n < 0x1000)
				ft_printf("%#.4x : ", n);
			n += 64;
		}
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
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", \
			i, data->champions[i - 1]->code_size, data->champions[i - 1]->name, \
			data->champions[i - 1]->comment);
		i++;
	}
}

void	print_last_alive(t_data *data)
{
	int	i;

	i = data->last_alive_champ;
	ft_printf("Contestant %d, \"%s\", has won !\n", \
	i, data->champions[i - 1]->name);
}

void	print_byte_jumps(t_process *cur_process, t_data *data)
{
	int	idx;
	int	i;

	if (data->verbosity & 0x10)
	{
		idx = cur_process->cursor;
		i = 0;
		ft_printf("ADV %d (0x%.4x -> 0x%.4x) ", \
		cur_process->byte_jump_size, idx, idx + cur_process->byte_jump_size);
		while (i < cur_process->byte_jump_size)
		{
			ft_printf("%.2x ", (uint8_t)data->arena[(idx + i) % MEM_SIZE]);
			i++;
		}
		ft_printf("\n");
	}
}
