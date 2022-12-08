/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:27:34 by wdonnell          #+#    #+#             */
/*   Updated: 2022/12/08 13:32:48 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

void	op_add(t_process *cur_process, t_data *data)
{
	t_types	types;
	int32_t	sum;

	types.size_t_dir = 4;
	types.num_args = 3;
	get_types(data->arena[cur_process->cursor + 1], &types);
	cur_process->byte_jump_size = jump_size(&types);
	if (types.type_arg[0] == T_REG && types.type_arg[1] == T_REG && types.type_arg[2] == T_REG)
	{
		if (get_arg_values(&data->arena[cur_process->cursor + 2], &types, cur_process))
		{
			sum = cur_process->registeries[types.val_arg[0] - 1] + cur_process->registeries[types.val_arg[1] - 1];
			cur_process->registeries[types.val_arg[2] - 1] = sum;
			update_carry(cur_process, sum);
		}
		if (data->verbosity & 0x04)
			ft_printf("P%5d | add r%d r%d r%d\n", cur_process->id, types.val_arg[0], types.val_arg[1], types.val_arg[2]);
	}
	if (data->verbosity & 0x10)
			print_byte_jumps(cur_process, data);
}

void	op_sub(t_process *cur_process, t_data *data)
{
	t_types	types;
	int32_t	diff;

	types.size_t_dir = 4;
	types.num_args = 3;
	get_types(data->arena[cur_process->cursor + 1], &types);
	cur_process->byte_jump_size = jump_size(&types);
	if (types.type_arg[0] == T_REG && types.type_arg[1] == T_REG && types.type_arg[2] == T_REG)
	{
		if (get_arg_values(&data->arena[cur_process->cursor + 2], &types, cur_process))
		{
			diff = cur_process->registeries[types.val_arg[0] - 1] - cur_process->registeries[types.val_arg[1] - 1];
			cur_process->registeries[types.val_arg[2] - 1] = diff;
			update_carry(cur_process, diff);
			if (data->verbosity & 0x04)
				ft_printf("P%5d | sub r%d r%d r%d\n", cur_process->id, types.val_arg[0], types.val_arg[1], types.val_arg[2]);
			
		}
	}
	if (data->verbosity & 0x10)
		print_byte_jumps(cur_process, data);
}
