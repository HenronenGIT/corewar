/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_store.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:27:54 by wdonnell          #+#    #+#             */
/*   Updated: 2022/12/05 15:47:37 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

void	op_st(t_process *cur_process, t_data *data)
{
	t_types	types;

	ft_printf("process %d is on 'st'\n", cur_process->id);
	types.size_t_dir = 4;
	types.num_args = 2;
	get_types(data->arena[cur_process->cursor + 1], &types);
	cur_process->byte_jump_size = jump_size(&types);
	if (types.type_arg[0] == T_REG && (types.type_arg[1] != T_DIR && types.type_arg[1] != T_NULL))
	{
		if (get_arg_values(&data->arena[cur_process->cursor + 2], &types, cur_process))
		{
			if (types.type_arg[1] == T_REG)
				cur_process->registeries[types.val_arg[0] - 1] = cur_process->registeries[types.val_arg[1] - 1];
			else
				cur_process->registeries[types.val_arg[0] - 1] = types.val_arg[1];
		}
	}
}

void	op_sti(t_process *cur_process, t_data *data)
{
	t_types	types;
	int		change;
	int		idx;

	types.size_t_dir = 2;
	types.num_args = 3;
	get_types(data->arena[cur_process->cursor + 1], &types);
	cur_process->byte_jump_size = jump_size(&types);
	if (types.type_arg[0] == T_REG && types.type_arg[2] != T_IND \
	&& !check_null(&types))
	{
		if (get_arg_values(&data->arena[cur_process->cursor + 2], &types, cur_process))
		{
			if (types.type_arg[1] == T_REG)
				types.val_arg[1] = cur_process->registeries[types.val_arg[1] - 1];
			if (types.type_arg[2] == T_REG)
				types.val_arg[2] = cur_process->registeries[types.val_arg[2] - 1];
			change = (types.val_arg[1] + types.val_arg[2]) % IDX_MOD;
			idx = circular_mem(cur_process->cursor, change);
			write_arena(&data->arena[idx], &cur_process->registeries[types.val_arg[0] - 1]);
			if (data->verbosity & 0x01)
				ft_printf("P%5d | sti r%d %d %d\n       | -> store to %d + %d = %d (with pc and mod %d)\n", \
				cur_process->id, types.val_arg[0], types.val_arg[1], types.val_arg[2], \
				types.val_arg[1], types.val_arg[2], types.val_arg[1] + types.val_arg[2], idx);
			if (data->verbosity & 0x02)
				print_byte_jumps(cur_process, data);
		}
	}
}
