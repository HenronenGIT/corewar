/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:27:05 by wdonnell          #+#    #+#             */
/*   Updated: 2022/12/10 14:47:17 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

//WIP
void	op_live(t_process *cur_process, t_data *data)
{
	//int player;

	cur_process->byte_jump_size = 5; //size of T_DIR + 1
	//count process as alive??
	cur_process->last_live = data->cycles_total;
	//count arg as last_alive_champ. Later check if this is a valid champ?
	data->last_alive_champ = bytes2int((uint8_t *)data->arena, cur_process->cursor + 1, 4);
	data->num_live_statements++;
	//are champ id's always negative??
	//player = data->last_alive_champ * -1;
	//if (player <= data->champions_num && player > 0)
	//	ft_printf("A process shows that player %d (%s) is alive\n", player, data->champions[player - 1]->name);
	if (data->verbosity & 0x04)
		ft_printf("P%5d | live %d\n", cur_process->id, data->last_alive_champ);
	if (data->verbosity & 0x10)
		print_byte_jumps(cur_process, data);
}

void	op_zjmp(t_process *cur_process, t_data *data)
{
	int	val;

	val = bytes2int((uint8_t *)data->arena, cur_process->cursor + 1, 2);
	if (cur_process->carry)
	{
		cur_process->cursor = circular_mem(cur_process->cursor, val);
		cur_process->byte_jump_size = 0;
	}
	else
		cur_process->byte_jump_size = 3; //size t_dir + 1
	if (data->verbosity & 0x04)
	{
		if (cur_process->carry)
			ft_printf("P%5d | zjmp %d OK\n", cur_process->id, val);
		else
		{
			ft_printf("P%5d | zjmp %d FAILED\n", cur_process->id, val);
			if (data->verbosity & 0x10)
				print_byte_jumps(cur_process, data);
		}
	}
}

//WIP
void	op_aff(t_process *cur_process, t_data *data)
{
	t_types types;

	ft_printf("process %d is on 'aff'\n", cur_process->id);
	types.size_t_dir = 4;
	types.num_args = 1;
	//sc + atc + 4
	get_types(data->arena[cur_process->cursor + 1], &types);
	//hardcoded in this case
	cur_process->byte_jump_size = 6;
	if (types.type_arg[0] == T_REG)
		if (get_arg_values(data->arena, cur_process->cursor + 2, &types, cur_process))
			ft_printf("AFF: %c\n", (char)cur_process->registeries[types.val_arg[0] - 1]);

}
