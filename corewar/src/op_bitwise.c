/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_bitwise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:27:38 by wdonnell          #+#    #+#             */
/*   Updated: 2022/12/05 15:41:54 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

void	op_and(t_process *cur_process, t_data *data)
{
	t_types	types;
	int32_t	val;

	types.size_t_dir = 4;
	types.num_args = 3;
	get_types(data->arena[cur_process->cursor + 1], &types);
	cur_process->byte_jump_size = jump_size(&types);
	if (types.type_arg[2] == T_REG && !check_null(&types))
	{
		if (get_arg_values(&data->arena[cur_process->cursor + 2], &types, cur_process))
		{
			if (types.type_arg[0] == T_REG)
				types.val_arg[0] = cur_process->registeries[types.val_arg[0] - 1];
			if (types.type_arg[1] == T_REG)
				types.val_arg[1] = cur_process->registeries[types.val_arg[1] - 1];
			val = (int32_t)(types.val_arg[0] & types.val_arg[1]);
			update_carry(cur_process, val);
			cur_process->registeries[types.val_arg[2] - 1] = val;
			if (data->verbosity & 0x01)
				ft_printf("P%5d | add %d %d r%d\n", cur_process->id, types.val_arg[0], types.val_arg[1], types.val_arg[2]);
			if (data->verbosity & 0x02)
				print_byte_jumps(cur_process, data);
		}
	}
}

//needs verbose mode in style of vm
void	op_or(t_process *cur_process, t_data *data)
{
	t_types	types;
	int32_t	val;

	ft_printf("process %d is on 'or'\n", cur_process->id);
	types.size_t_dir = 4;
	types.num_args = 3;
	get_types(data->arena[cur_process->cursor + 1], &types);
	cur_process->byte_jump_size = jump_size(&types);
	if (types.type_arg[2] == T_REG && !check_null(&types))
	{
		if (get_arg_values(&data->arena[cur_process->cursor + 2], &types, cur_process))
		{
			if (types.type_arg[0] == T_REG)
				types.val_arg[0] = cur_process->registeries[types.val_arg[0] - 1];
			if (types.type_arg[1] == T_REG)
				types.val_arg[1] = cur_process->registeries[types.val_arg[1] - 1];
			val = (int32_t)(types.val_arg[0] | types.val_arg[1]);
			update_carry(cur_process, val);
			cur_process->registeries[types.val_arg[2] - 1] = val;
			if (data->verbosity & 0x01)
				ft_printf("executed 'or' -wrote %d to regristry %d\n", val, types.val_arg[2]);
			if (data->verbosity & 0x02)
				print_byte_jumps(cur_process, data);
		}
	}
}

//needs verbose mode in style of vm
void	op_xor(t_process *cur_process, t_data *data)
{
	t_types	types;
	int32_t	val;

	ft_printf("process %d is on 'xor'\n", cur_process->id);
	types.size_t_dir = 4;
	types.num_args = 3;
	get_types(data->arena[cur_process->cursor + 1], &types);
	cur_process->byte_jump_size = jump_size(&types);
	if (types.type_arg[2] == T_REG && !check_null(&types))
	{
		if (get_arg_values(&data->arena[cur_process->cursor + 2], &types, cur_process))
		{
			if (types.type_arg[0] == T_REG)
				types.val_arg[0] = cur_process->registeries[types.val_arg[0] - 1];
			if (types.type_arg[1] == T_REG)
				types.val_arg[1] = cur_process->registeries[types.val_arg[1] - 1];
			val = (int32_t)(types.val_arg[0] ^ types.val_arg[1]);
			update_carry(cur_process, val);
			cur_process->registeries[types.val_arg[2] - 1] = val;
			if (data->verbosity & 0x01)
				ft_printf("executed 'xor' -wrote %d to regristry %d\n", val, types.val_arg[2]);
			if (data->verbosity & 0x02)
				print_byte_jumps(cur_process, data);
		}
	}
}
