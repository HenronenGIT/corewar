/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:27:05 by wdonnell          #+#    #+#             */
/*   Updated: 2022/12/13 12:30:49 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

void	op_live(t_process *process, t_data *data)
{
	int	val;

	process->byte_jump_size = 5; //size of T_DIR + 1
	process->last_live = data->cycles_total;
	val = bytes2int((uint8_t *)data->arena, process->cursor + 1, 4);
	data->num_live_statements++;
	 if (val && ft_abs(val) <= data->champions_num)
	{
		data->last_alive_champ = ft_abs(val);
		//ft_printf("A process shows that player %d (%s) is alive\n", ft_abs(val), data->champions[ft_abs(val) - 1]->name);
	}
	if (data->verbosity & 0x04)
		ft_printf("P%5d | live %d\n", process->id, val);
	if (data->verbosity & 0x10)
		print_byte_jumps(process, data);
}

void	op_zjmp(t_process *process, t_data *data)
{
	int	val;

	val = bytes2int((uint8_t *)data->arena, process->cursor + 1, 2);
	if (process->carry)
	{
		process->cursor = circular_mem(process->cursor, val % IDX_MOD);
		process->byte_jump_size = 0;
	}
	else
		process->byte_jump_size = 3; //size t_dir + 1
	if (data->verbosity & 0x04)
	{
		if (process->carry)
			ft_printf("P%5d | zjmp %d OK\n", process->id, val);
		else
		{
			ft_printf("P%5d | zjmp %d FAILED\n", process->id, val);
			if (data->verbosity & 0x10)
				print_byte_jumps(process, data);
		}
	}
}

//WIP
void	op_aff(t_process *process, t_data *data)
{
	t_types types;

	ft_printf("process %d is on 'aff'\n", process->id);
	types.size_t_dir = 4;
	types.num_args = 1;
	//sc + atc + 4
	get_types(data->arena[process->cursor + 1], &types);
	//hardcoded in this case
	process->byte_jump_size = 6;
	if (types.type_arg[0] == T_REG)
		if (get_arg_values(data->arena, process->cursor + 2, &types, process))
			ft_printf("AFF: %c\n", (char)process->registers[types.val_arg[0] - 1]);

}
