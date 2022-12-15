/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:27:34 by wdonnell          #+#    #+#             */
/*   Updated: 2022/12/15 13:02:16 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

void	op_add(t_process *process, t_data *data)
{
	t_types	types;
	int32_t	sum;

	types.size_t_dir = 4;
	types.num_args = 3;
	get_types(data, process, &types);
	if (types.type_arg[0] == T_REG && types.type_arg[1] == T_REG \
	&& types.type_arg[2] == T_REG)
	{
		if (get_arg_values(data, &types, process))
		{
			sum = process->registers[types.val_arg[0] - 1] \
			+ process->registers[types.val_arg[1] - 1];
			process->registers[types.val_arg[2] - 1] = sum;
			update_carry(process, sum);
			if (data->verbosity & 0x04)
				ft_printf("P%5d | add r%d r%d r%d\n", process->id, \
				types.val_arg[0], types.val_arg[1], types.val_arg[2]);
		}
	}
	print_byte_jumps(process, data);
}

void	op_sub(t_process *process, t_data *data)
{
	t_types	types;
	int32_t	diff;

	types.size_t_dir = 4;
	types.num_args = 3;
	get_types(data, process, &types);
	if (types.type_arg[0] == T_REG && types.type_arg[1] == T_REG \
	&& types.type_arg[2] == T_REG)
	{
		if (get_arg_values(data, &types, process))
		{
			diff = process->registers[types.val_arg[0] - 1] \
			- process->registers[types.val_arg[1] - 1];
			process->registers[types.val_arg[2] - 1] = diff;
			update_carry(process, diff);
			if (data->verbosity & 0x04)
				ft_printf("P%5d | sub r%d r%d r%d\n", process->id, \
				types.val_arg[0], types.val_arg[1], types.val_arg[2]);
		}
	}
	print_byte_jumps(process, data);
}
