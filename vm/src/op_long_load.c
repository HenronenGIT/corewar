/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_long_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:49:48 by wdonnell          #+#    #+#             */
/*   Updated: 2023/01/11 21:52:44 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

void	op_lld(t_process *process, t_data *data)
{
	t_types	types;
	int32_t	val;

	types.size_t_dir = 4;
	types.num_args = 2;
	get_types(data, process, &types);
	if (types.type_arg[1] == T_REG && (types.type_arg[0] != T_REG \
	&& types.type_arg[0] != T_NULL))
	{
		if (get_arg_values(data, &types, process))
		{
			val = types.val_arg[0];
			process->registers[types.val_arg[1] - 1] = val;
			update_carry(process, val);
			if (data->verbosity & 0x04)
				ft_printf("P%5d | lld %d r%d\n", process->id, \
				types.val_arg[0], types.val_arg[1]);
		}
	}
	print_byte_jumps(process, data);
}

static void	lldi_verbose(t_data *data, t_process *process, \
t_types *types, int change)
{
	if (data->verbosity & 0x04)
	{
		ft_printf("P%5d | lldi %d %d r%d\n", \
		process->id, types->val_arg[0], types->val_arg[1], types->val_arg[2]);
		ft_printf("       | -> load from %d + %d = %d (with pc %d)\n", \
		types->val_arg[0], types->val_arg[1], change, change + process->cursor);
	}
}

void	op_lldi(t_process *process, t_data *data)
{
	t_types	types;
	int		change;
	int		idx;

	types.size_t_dir = 2;
	types.num_args = 3;
	get_types(data, process, &types);
	if (types.type_arg[2] == T_REG && types.type_arg[1] != T_IND \
	&& !check_null(&types))
	{
		if (get_arg_values(data, &types, process))
		{
			if (types.type_arg[0] == T_REG)
				types.val_arg[0] = process->registers[types.val_arg[0] - 1];
			if (types.type_arg[1] == T_REG)
				types.val_arg[1] = process->registers[types.val_arg[1] - 1];
			change = types.val_arg[0] + types.val_arg[1];
			idx = circular_mem(process->cursor, change);
			process->registers[types.val_arg[2] - 1] \
			= bytes2int((uint8_t *)data->arena, idx, 4);
			update_carry(process, process->registers[types.val_arg[2] - 1]);
			lldi_verbose(data, process, &types, change);
		}
	}
	print_byte_jumps(process, data);
}
