/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_store.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:27:54 by wdonnell          #+#    #+#             */
/*   Updated: 2022/12/15 13:01:50 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

static void	st_verbose(t_data *data, t_process *process, t_types *types)
{
	if (data->verbosity & 0x04)
		ft_printf("P%5d | st r%d %d\n", process->id, \
		types->val_arg[0], types->val_arg[1]);
}

void	op_st(t_process *process, t_data *data)
{
	t_types	types;
	int		idx;

	types.size_t_dir = 4;
	types.num_args = 2;
	get_types(data, process, &types);
	if (types.type_arg[0] == T_REG && (types.type_arg[1] == T_REG \
	|| types.type_arg[1] == T_IND))
	{
		if (get_arg_values(data, &types, process))
		{
			if (types.type_arg[1] == T_REG)
				process->registers[types.val_arg[1] - 1] \
				= process->registers[types.val_arg[0] - 1];
			else
			{
				idx = circular_mem(process->cursor, types.val_arg[1] % IDX_MOD);
				write_arena(data->arena, idx, \
				&process->registers[types.val_arg[0] - 1]);
			}
			st_verbose(data, process, &types);
		}
	}
	print_byte_jumps(process, data);
}

static void	sti_verbose(t_data *data, t_process *process, \
t_types	*types, int change)
{
	if (data->verbosity & 0x04)
	{
		ft_printf("P%5d | sti r%d %d %d\n", \
		process->id, types->val_arg[0], types->val_arg[1], types->val_arg[2]);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", \
		types->val_arg[1], types->val_arg[2], \
		types->val_arg[1] + types->val_arg[2], process->cursor + change);
	}
}

void	op_sti(t_process *process, t_data *data)
{
	t_types	types;
	int		change;
	int		idx;

	types.size_t_dir = 2;
	types.num_args = 3;
	get_types(data, process, &types);
	if (types.type_arg[0] == T_REG && types.type_arg[2] != T_IND \
	&& !check_null(&types))
	{
		if (get_arg_values(data, &types, process))
		{
			if (types.type_arg[1] == T_REG)
				types.val_arg[1] = process->registers[types.val_arg[1] - 1];
			if (types.type_arg[2] == T_REG)
				types.val_arg[2] = process->registers[types.val_arg[2] - 1];
			change = (types.val_arg[1] + types.val_arg[2]) % IDX_MOD;
			idx = circular_mem(process->cursor, change);
			write_arena(data->arena, idx, \
			&process->registers[types.val_arg[0] - 1]);
			sti_verbose(data, process, &types, change);
		}
	}
	print_byte_jumps(process, data);
}
