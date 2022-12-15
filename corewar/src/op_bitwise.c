/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_bitwise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:27:38 by wdonnell          #+#    #+#             */
/*   Updated: 2022/12/14 21:18:01 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

void	op_and(t_process *process, t_data *data)
{
	t_types	types;
	int32_t	val;

	types.size_t_dir = 4;
	types.num_args = 3;
	get_types(data, process, &types);
	if (types.type_arg[2] == T_REG && !check_null(&types))
	{
		if (get_arg_values(data, &types, process))
		{
			if (types.type_arg[0] == T_REG)
				types.val_arg[0] = process->registers[types.val_arg[0] - 1];
			if (types.type_arg[1] == T_REG)
				types.val_arg[1] = process->registers[types.val_arg[1] - 1];
			val = (int32_t)(types.val_arg[0] & types.val_arg[1]);
			update_carry(process, val);
			process->registers[types.val_arg[2] - 1] = val;
			if (data->verbosity & 0x04)
				ft_printf("P%5d | and %d %d r%d\n", process->id, \
				types.val_arg[0], types.val_arg[1], types.val_arg[2]);
		}
	}
	if (data->verbosity & 0x10)
		print_byte_jumps(process, data);
}

void	op_or(t_process *process, t_data *data)
{
	t_types	types;
	int32_t	val;

	types.size_t_dir = 4;
	types.num_args = 3;
	get_types(data, process, &types);
	if (types.type_arg[2] == T_REG && !check_null(&types))
	{
		if (get_arg_values(data, &types, process))
		{
			if (types.type_arg[0] == T_REG)
				types.val_arg[0] = process->registers[types.val_arg[0] - 1];
			if (types.type_arg[1] == T_REG)
				types.val_arg[1] = process->registers[types.val_arg[1] - 1];
			val = (int32_t)(types.val_arg[0] | types.val_arg[1]);
			update_carry(process, val);
			process->registers[types.val_arg[2] - 1] = val;
			if (data->verbosity & 0x04)
				ft_printf("P%5d | or %d %d r%d\n", process->id, \
				types.val_arg[0], types.val_arg[1], types.val_arg[2]);
		}
	}
	if (data->verbosity & 0x10)
		print_byte_jumps(process, data);
}

void	op_xor(t_process *process, t_data *data)
{
	t_types	types;
	int32_t	val;

	types.size_t_dir = 4;
	types.num_args = 3;
	get_types(data, process, &types);
	if (types.type_arg[2] == T_REG && !check_null(&types))
	{
		if (get_arg_values(data, &types, process))
		{
			if (types.type_arg[0] == T_REG)
				types.val_arg[0] = process->registers[types.val_arg[0] - 1];
			if (types.type_arg[1] == T_REG)
				types.val_arg[1] = process->registers[types.val_arg[1] - 1];
			val = (int32_t)(types.val_arg[0] ^ types.val_arg[1]);
			update_carry(process, val);
			process->registers[types.val_arg[2] - 1] = val;
			if (data->verbosity & 0x04)
				ft_printf("P%5d | xor %d %d r%d\n", process->id, \
				types.val_arg[0], types.val_arg[1], types.val_arg[2]);
		}
	}
	if (data->verbosity & 0x10)
		print_byte_jumps(process, data);
}
