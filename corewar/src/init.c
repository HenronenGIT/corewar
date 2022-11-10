/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:38:58 by akilk             #+#    #+#             */
/*   Updated: 2022/11/10 12:06:24 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

t_champion	*init_champion(int id)
{
	t_champion	*new_champion;

	new_champion = (t_champion *)ft_memalloc(sizeof (t_champion));
	if (!new_champion)
		error(NULL, "Allocation failed in init_champion()");
	new_champion->name = NULL;
	new_champion->comment = NULL;
	new_champion->code_size = 0;
	new_champion->code = 0;
	return (new_champion);
}

void	init_vm(t_vm *vm)
{
	vm->champions_num = 0;
}

void	load_arena(t_vm *vm)
{
	int	current;
	int	start;

	current = 0;
	start = 0;
	while (current < vm->champions_num)
	{
		start = (current * MEM_SIZE) / vm->champions_num;
		printf("addr: %p, %d\n", start, vm->champions[current]->code_size);
		ft_memcpy(&(vm->arena[start]), vm->champions[current]->code,
					vm->champions[current]->code_size);
		current++;
	}

}
/* to check addresses */
// 		printf("addr: %p, %d\n", start, vm->champions[current]->code_size);
