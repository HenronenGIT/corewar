/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:04:25 by wdonnell          #+#    #+#             */
/*   Updated: 2022/11/22 14:50:28 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

/*
//tester
static void print_registers(t_process *temp)
{
	int i;
	int j;

	i = 0;
	ft_printf("\nProcess %d Regristries--->\n", temp->id);
	while (i < REG_NUMBER)
	{
		j = 31;
		ft_printf("reg %.2d: ", i + 1);
		while (j >= 0)
		{
			ft_printf("%c", temp->registeries[i] & (int32_t)ft_pow( 2, j) ? '1' : '0' );
			if (j % 8 == 0)
				ft_printf(" ");
			j--;
		}
		ft_printf("\n");
		i++;
	}
}
*/
static void read_statement_code(t_data *data, t_process *temp)
{
	int cycles_remaining[16] = \
	{10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800, 10, 50, 1000, 2};
	int8_t n;

	//check if valid and set cycles remaining
	n = data->arena[temp->cursor] - 1;
	if (n < 16 && n >= 0)
	{
		temp->statement_code = n;
		temp->cycles_remaining = cycles_remaining[n];
	}
	else
		//invalid op code
		//move cursor forward 1 byte and go to next process
		temp->cursor++;

}

static void check_process(t_data *data, t_process *temp)
{
	if (temp->cycles_remaining == -1)
	{
		//move cursor to next position
		temp->cursor = circular_mem(temp->cursor, temp->byte_jump_size);
		read_statement_code(data, temp);
	}
	else if (temp->cycles_remaining == 0)
		//execute temp->statement_code
		g_dispatch[temp->statement_code](temp, data);
		//inside functions
		//set cycles remaing to -1
		//set byte jump size
	else if (temp->cycles_remaining)
		//decrease cycles_remaining
		temp->cycles_remaining--;
}

/* updated version */


static void	execute_processes(t_data *data, t_process *head)
{
	t_process *temp;

	temp = head;
	
	data->cycles_passed++;
	data->cycles_after_check++;
	while (temp)
	{
		check_process(data, temp);
		printf("id: %d cyc rem: %d\n", temp->id, temp->cycles_remaining);
		temp = temp->next;
	}
	
}


void play_game(t_data *data, t_process *head)
{
	/* outer cycle plays until there are processes left. */
	while (data->cursors_num)
	{
		//print if -dump flag used
		if (data->dump_cycle == data->cycles_passed)
			print_data(data);
		/* inner cycle plays every process in list */
		execute_processes(data, head);
		// perform check
		if (data->cycles_to_die == data->cycles_after_check
			|| data->cycles_to_die <= 0)
			check(data, head);
	}
}
