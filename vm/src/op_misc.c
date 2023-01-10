/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:27:05 by wdonnell          #+#    #+#             */
/*   Updated: 2023/01/10 14:29:44 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

/*
** changed to work with only negative player id's
*/

void	op_live(t_process *process, t_data *data)
{
	int	val;

	process->byte_jump_size = 5;
	process->last_live = data->cycles_total;
	val = bytes2int((uint8_t *)data->arena, \
	(process->cursor + 1) % MEM_SIZE, 4);
	data->num_live_statements++;
	if (val && val < 0 && ft_abs(val) <= data->champions_num)
	{
		data->last_alive_champ = ft_abs(val);
		if (!(data->verbosity & 0x01))
			ft_printf("A process shows that player %d (%s) is alive\n", \
			ft_abs(val), data->champions[ft_abs(val) - 1]->name);
	}
	if (data->verbosity & 0x04)
		ft_printf("P%5d | live %d\n", process->id, val);
	print_byte_jumps(process, data);
}

void	op_zjmp(t_process *process, t_data *data)
{
	int	val;

	val = bytes2int((uint8_t *)data->arena, \
	(process->cursor + 1) % MEM_SIZE, 2);
	if (process->carry)
	{
		process->cursor = circular_mem(process->cursor, val % IDX_MOD);
		process->byte_jump_size = 0;
	}
	else
		process->byte_jump_size = 3;
	if (data->verbosity & 0x04)
	{
		if (process->carry)
			ft_printf("P%5d | zjmp %d OK\n", process->id, val);
		else
		{
			ft_printf("P%5d | zjmp %d FAILED\n", process->id, val);
		}
	}
	if ((data->verbosity & 0x10) && !process->carry)
		print_byte_jumps(process, data);
}

void	op_aff(t_process *process, t_data *data)
{
	t_types	types;

	types.size_t_dir = 4;
	types.num_args = 1;
	get_types(data, process, &types);
	if (types.type_arg[0] == T_REG)
		if (get_arg_values(data, &types, process) && !(data->verbosity & 0x01))
			ft_printf("Aff: %c\n", \
			(char)process->registers[types.val_arg[0] - 1]);
	print_byte_jumps(process, data);
}
