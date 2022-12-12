/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:27:43 by wdonnell          #+#    #+#             */
/*   Updated: 2022/12/10 11:36:00 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

void	op_fork(t_process *process, t_data *data)
{
	int	idx;

	++data->num_processes;
	process->byte_jump_size = 3;
	idx = bytes2int((uint8_t *)data->arena, process->cursor + 1, 2);
	data->new_cursor = circular_mem(process->cursor, idx % IDX_MOD);
	data->parent = process;
	add_process(data, &data->head, ++data->new_process_id);
	if (data->verbosity & 0x04)
		ft_printf("P%5d | fork %d (%d)\n", process->id, idx, data->new_cursor);
	if (data->verbosity & 0x10)
		print_byte_jumps(process, data);
}

void	op_lfork(t_process *process, t_data *data)
{
	int	idx;

	process->byte_jump_size = 3;
	idx = bytes2int((uint8_t *)data->arena, process->cursor + 1, 2);
	data->new_cursor = circular_mem(process->cursor, idx);
	data->parent = process;
	add_process(data, &data->head, ++data->new_process_id);
	if (data->verbosity & 0x04)
		ft_printf("P%5d | lfork %d (%d)\n", process->id, \
		idx, process->cursor + idx);
	if (data->verbosity & 0x10)
		print_byte_jumps(process, data);
}
