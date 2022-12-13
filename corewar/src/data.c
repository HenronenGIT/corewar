/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:43:53 by wdonnell          #+#    #+#             */
/*   Updated: 2022/12/13 11:04:10 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void init_arena(int8_t *arena)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
		arena[i++] = 0;
}

void	init_data(t_data *data)
{
	init_arena(data->arena);
	data->champions_num = 0; // add to init_data
	//init w/ pointer to champ with highest id
	// data->last_alive = data->champions[data->champions_num - 1];
	data->num_processes = 0;
	data->cycles_total = 0;
	data->num_live_statements = 0;
	data->cycles_to_die = CYCLE_TO_DIE;
	data->cycles_after_check = 0;
	data->num_checks_performed = 0;
	data->dump_cycle = -1;
	//how to init?
	data->last_alive_champ = 1;
	data->verbosity = 0;
	//data->new_process_id = 0;
	data->head = NULL;

}
