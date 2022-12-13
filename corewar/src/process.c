/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:55:35 by wdonnell          #+#    #+#             */
/*   Updated: 2022/11/10 16:09:21 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void copy_parent_registers(int32_t *fork_registers, int32_t *parent_registers)
{
	int i;

	i = 0;
	while (i < REG_NUMBER)
	{
		fork_registers[i] = parent_registers[i];
		i++;
	}
}

static void init_process_registers(int32_t *registers, int i)
{
	int n;

	registers[0] = -i;
	n = 1;
	while (n < REG_NUMBER)
		registers[n++] = 0;
}

static void init_process(t_data *data, t_process *temp, int i)
{
	temp->id = i;
	temp->carry = false;
	temp->cursor = data->champions[i - 1]->start_addr;
	temp->last_live = 0;
	temp->cycles_remaining = -1;
	temp->byte_jump_size = 0;

	init_process_registers(temp->registers, i);
}

static void init_fork(t_data *data, t_process *temp, int i)
{
	temp->id = i;
	temp->carry = data->parent->carry;
	temp->cursor = data->new_cursor;
	temp->last_live = data->parent->last_live;
	temp->cycles_remaining = -1;
	temp->byte_jump_size = 0;

	copy_parent_registers(temp->registers, data->parent->registers);
}

void add_process(t_data *data, t_process **head, int i)
{
	t_process *temp;

	temp = malloc(sizeof(t_process));
	if (!temp)
		error(NULL, "Allocation failed in add_process", 0);
	if (*head == NULL)
		temp->next = NULL;
	else
		temp->next = *head;
	if (!data->cycles_total)
		init_process(data, temp, i);
	else
		init_fork(data, temp, i);
	*head = temp;
}

void create_processes(t_data *data)
{
	int i;
	t_process **head;

	head = &data->head;
	i = 1;
	//printf("champs_num-> %d\n", data->champions_num);
	while (i <= data->champions_num)
	{
		//malloc process and add to list
		add_process(data, head, i);
		data->num_processes++;
		i++;
	}
	data->new_process_id = data->num_processes;
}