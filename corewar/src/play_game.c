/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:04:25 by wdonnell          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/16 14:30:01 by wdonnell         ###   ########.fr       */
=======
/*   Updated: 2022/11/15 14:52:11 by wdonnell         ###   ########.fr       */
>>>>>>> 6dd10a71479dcc9665ed89a2170ae37e550214aa
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

static void execute(t_process *temp, t_data *data)
{
	int n;

	n = data->arena[temp->cursor] - 1;
	if (n < 16 && n >= 0)
		g_dispatch[n](temp, data);
	else
		printf("invalid op code\n");
		//invalid op code

}

void play_game(t_data *data, t_process *head)
{
	t_process *temp;

	temp = head;

	execute(temp, data);
	/*
	while //some condition related to cycles
	{
		temp = head;
		while (temp)
		{
			//execute current process
			execute(temp, data);
			temp = temp->next;
		}
		//do whatever checks
		data->cycles_passed++;
	}
	*/
}
