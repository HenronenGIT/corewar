/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:04:25 by wdonnell          #+#    #+#             */
/*   Updated: 2022/11/17 11:24:15 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

//include for tester , pow()
#include <math.h>

//tester
static void print_registers(t_process *temp)
{
	int i = 0;

	printf("\nProcess %d Regristries--->\n", temp->id);
	while (i < REG_NUMBER)
	{
		//int version
		printf("reg %.2d: ", i + 1);
		for (int j = 31; j >= 0; j--)
		{
			printf("%c", temp->registeries[i] & (int32_t)pow( 2, j) ? '1' : '0' );
			if (j % 8 == 0)
				printf(" ");
		}
		printf("\n");
		i++;
	}
}

static void execute(t_process *temp, t_data *data)
{
	int n;

	n = data->arena[temp->cursor] - 1;
	if (n < 16 && n >= 0)
		g_dispatch[n](temp, data);
	else
		ft_printf("invalid op code\n");
		//invalid op code

}

void play_game(t_data *data, t_process *head)
{
	t_process *temp;

	//temp = head;

	//execute(temp, data);
	//print_registers(temp);
	
	//while //some condition related to cycles
	//{
		temp = head;
		while (temp)
		{
			//execute current process
			execute(temp, data);
			//print_registers(temp);
			temp = temp->next;
		}
		//do whatever checks
		data->cycles_passed++;
	//}
	
}
