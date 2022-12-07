/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:27:48 by wdonnell          #+#    #+#             */
/*   Updated: 2022/12/06 17:11:13 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

void	op_ld(t_process *cur_process, t_data *data)
{
	t_types	types;

	types.size_t_dir = 4;
	types.num_args = 2;
	get_types(data->arena[cur_process->cursor + 1], &types);
	cur_process->byte_jump_size = jump_size(&types);
	if (types.type_arg[1] == T_REG && (types.type_arg[0] != T_REG && types.type_arg[0] != T_NULL))
	{
		if (get_arg_values(&data->arena[cur_process->cursor + 2], &types, cur_process))
		{
			cur_process->registeries[types.val_arg[1] - 1] = types.val_arg[0];
			update_carry(cur_process, types.val_arg[0]);
			if (data->verbosity & 0x01)
				ft_printf("P%5d | ld %d r%d\n", cur_process->id, types.val_arg[0], types.val_arg[1]);
		}
	}
	if (data->verbosity & 0x02)
		print_byte_jumps(cur_process, data);
}

void	op_ldi(t_process *cur_process, t_data *data)
{
	t_types	types;
	int		change;
	int		idx;

	types.size_t_dir = 2;
	types.num_args = 3;
	get_types(data->arena[cur_process->cursor + 1], &types);
	cur_process->byte_jump_size = jump_size(&types);
	if (types.type_arg[1] != T_IND && types.type_arg[2] == T_REG \
	&& !check_null(&types))
	{
		if (get_arg_values(&data->arena[cur_process->cursor + 2], &types, cur_process))
		{
			if (types.type_arg[0] == T_REG)
				types.val_arg[0] = cur_process->registeries[types.val_arg[0] - 1];
			if (types.type_arg[1] == T_REG)
				types.val_arg[1] = cur_process->registeries[types.val_arg[1] - 1];
			change = (types.val_arg[0] + types.val_arg[1]) % IDX_MOD;
			idx = circular_mem(cur_process->cursor, change);
			cur_process->registeries[types.val_arg[2] - 1] = bytes2int((uint8_t *)&data->arena[idx], 4);
			if (data->verbosity & 0x01)
				ft_printf("P%5d | ldi %d %d r%d\n       | -> load from %d + %d = %d (with pc and mod %d)\n", \
				cur_process->id, types.val_arg[0], types.val_arg[1], types.val_arg[2], \
				types.val_arg[0], types.val_arg[1], types.val_arg[0] + types.val_arg[1], idx);
			
		}
	}
	if (data->verbosity & 0x02)
		print_byte_jumps(cur_process, data);
}

void	op_lld(t_process *cur_process, t_data *data)
{
	t_types	types;
	int32_t	val;
	int		idx;

	ft_printf("process %d is on 'lld'\n", cur_process->id);
	types.size_t_dir = 4;
	types.num_args = 2;
	get_types(data->arena[cur_process->cursor + 1], &types);
	cur_process->byte_jump_size = jump_size(&types);
	if (types.type_arg[1] == T_REG && (types.type_arg[0] != T_REG && types.type_arg[0] != T_NULL))
	{
		if (get_arg_values(&data->arena[cur_process->cursor + 2], &types, cur_process))
		{
			idx = circular_mem(cur_process->cursor, types.val_arg[0]);
			val = bytes2int((uint8_t *)&data->arena[idx], 4);
			cur_process->registeries[types.val_arg[1] - 1] = val;
			update_carry(cur_process, val);
		}
	}
}

void	op_lldi(t_process *cur_process, t_data *data)
{
	t_types	types;
	int		change;
	int		idx;

	ft_printf("process %d is on 'lldi'\n", cur_process->id);
	types.size_t_dir = 2;
	types.num_args = 3;
	get_types(data->arena[cur_process->cursor + 1], &types);
	cur_process->byte_jump_size = jump_size(&types);
	if (types.type_arg[2] == T_REG && types.type_arg[1] != T_IND \
	&& !check_null(&types))
	{
		if (get_arg_values(&data->arena[cur_process->cursor + 2], &types, cur_process))
		{
			if (types.type_arg[0] == T_REG)
				types.val_arg[0] = cur_process->registeries[types.val_arg[0] - 1];
			if (types.type_arg[1] == T_REG)
				types.val_arg[1] = cur_process->registeries[types.val_arg[1] - 1];
			change = types.val_arg[0] + types.val_arg[1];
			idx = circular_mem(cur_process->cursor, change);
			cur_process->registeries[types.val_arg[2] - 1] = bytes2int((uint8_t *)&data->arena[idx], 4);
			update_carry(cur_process, cur_process->registeries[types.val_arg[2] - 1]);
		}
	}
}
