/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process_and_fork.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:43:38 by wdonnell          #+#    #+#             */
/*   Updated: 2022/12/15 14:42:12 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	copy_parent_registers(int32_t *fork_registers, \
int32_t *parent_registers)
{
	int	i;

	i = 0;
	while (i < REG_NUMBER)
	{
		fork_registers[i] = parent_registers[i];
		i++;
	}
}

static void	init_process_registers(int32_t *registers, int i)
{
	int	n;

	registers[0] = -i;
	n = 1;
	while (n < REG_NUMBER)
		registers[n++] = 0;
}

void	init_process(t_data *data, t_process *temp, int i)
{
	temp->id = i;
	temp->carry = false;
	temp->cursor = data->champions[i - 1]->start_addr;
	temp->last_live = 0;
	temp->cycles_remaining = -1;
	temp->byte_jump_size = 0;
	init_process_registers(temp->registers, i);
}

void	init_fork(t_data *data, t_process *temp, int i)
{
	temp->id = i;
	temp->carry = data->parent->carry;
	temp->cursor = data->new_cursor;
	temp->last_live = data->parent->last_live;
	temp->cycles_remaining = -1;
	temp->byte_jump_size = 0;
	copy_parent_registers(temp->registers, data->parent->registers);
}
