/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:04:25 by wdonnell          #+#    #+#             */
/*   Updated: 2022/12/13 13:34:59 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

static void	read_statement_code(t_data *data, t_process *temp)
{
	static const int	cycles_remaining[16] = \
	{10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800, 10, 50, 1000, 2};
	int8_t		n;

	n = data->arena[temp->cursor] - 1;
	if (n < 16 && n >= 0)
	{
		temp->statement_code = n;
		temp->cycles_remaining = cycles_remaining[n];
		temp->cycles_remaining--;
	}
	else
	{
		temp->byte_jump_size = 0;
		temp->cursor = (temp->cursor + 1) % MEM_SIZE;
	}
}

static void check_process(t_data *data, t_process *temp)
{
	if (temp->cycles_remaining == -1)
	{
		temp->cursor = circular_mem(temp->cursor, temp->byte_jump_size);
		read_statement_code(data, temp);
	}
	else if (temp->cycles_remaining == 1)
	{
		g_dispatch[temp->statement_code](temp, data);
		temp->cycles_remaining = -1;
	}
	else if (temp->cycles_remaining)
		temp->cycles_remaining--;
}

static void	execute_processes(t_data *data, t_process *head)
{
	t_process	*temp;

	temp = head;
	data->cycles_total++;
	data->cycles_after_check++;
	if (data->verbosity & 0x02)
		ft_printf("It is now cycle %d\n", data->cycles_total);
	while (temp)
	{
		check_process(data, temp);
		temp = temp->next;
	}
}

void	play_game(t_data *data)
{
	while (data->num_processes > 0)
	{
		if (data->dump_cycle == data->cycles_total)
			print_data(data);
		execute_processes(data, data->head);
		if (data->cycles_to_die == data->cycles_after_check
			|| data->cycles_to_die <= 0)
			check(data, &data->head);
	}
}
