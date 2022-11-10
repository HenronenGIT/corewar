/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:43:53 by wdonnell          #+#    #+#             */
/*   Updated: 2022/11/10 10:56:27 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	init_data(t_data *data, t_vm *vm)
{
	//init w/ pointer to champ with highest id
	data->last_alive = (t_champion *)vm->champions[vm->champions_num - 1];
	data->cycles_passed = 0;
	data->num_live_statements = 0;
	data->cycles_to_die = CYCLE_TO_DIE;
	data->num_checks_performed = 0;
}
