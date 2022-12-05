/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:27:43 by wdonnell          #+#    #+#             */
/*   Updated: 2022/12/05 15:44:45 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

void	op_fork(t_process *cur_process, t_data *data)
{
	int	idx;

	cur_process->byte_jump_size = 3; //size of T_DIR + 1
	idx = bytes2int((uint8_t *)&data->arena[cur_process->cursor + 1], 2) % IDX_MOD;
	data->new_cursor = circular_mem(cur_process->cursor, idx);
	data->parent = cur_process;
	add_process(data, &data->head, ++data->num_processes);
	if (data->verbosity & 0x01)
		ft_printf("P%5d | fork %d (%d)\n", cur_process->id, idx, data->new_cursor);
	if (data->verbosity & 0x02)
		print_byte_jumps(cur_process, data);
}

void	op_lfork(t_process *cur_process, t_data *data)
{
	int	idx;

	cur_process->byte_jump_size = 3; //size of T_DIR + 1
	idx = bytes2int((uint8_t *)&data->arena[cur_process->cursor + 1], 2);
	data->new_cursor = circular_mem(cur_process->cursor, idx);
	data->parent = cur_process;
	add_process(data, &data->head, ++data->num_processes);
	if (data->verbosity & 0x01)
		ft_printf("P%5d | lfork %d (%d)\n", cur_process->id, idx, data->new_cursor);
	if (data->verbosity & 0x02)
		print_byte_jumps(cur_process, data);
}
