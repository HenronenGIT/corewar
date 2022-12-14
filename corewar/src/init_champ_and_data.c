/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:38:58 by akilk             #+#    #+#             */
/*   Updated: 2022/12/14 16:38:42 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

t_champion	*init_champion(void)
{
	t_champion	*new_champion;

	new_champion = (t_champion *)ft_memalloc(sizeof (t_champion));
	if (!new_champion)
		error(NULL, "Allocation failed in init_champion()", 0);
	new_champion->id = 0;
	new_champion->name = NULL;
	new_champion->comment = NULL;
	new_champion->code_size = 0;
	new_champion->code = 0;
	new_champion->start_addr = 0;
	return (new_champion);
}

static void	init_arena(int8_t *arena)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
		arena[i++] = 0;
}

void	init_data(t_data *data)
{
	init_arena(data->arena);
	data->champions_num = 0;
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
	data->head = NULL;
}
