/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:38:58 by akilk             #+#    #+#             */
/*   Updated: 2022/11/08 07:15:23 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	init_champion(t_champion *champion)
{
	t_champion	*new_champion;

	new_champion = (t_champion *)ft_memalloc(sizeof (t_champion));
	if (!new_champion)
		exit (1); //add error msg?
}

void	init_vm(t_vm *vm)
{
	vm = (t_vm *)ft_memalloc(sizeof (t_vm));
	if (!vm)
		exit (1); //add error msg?
	vm->champions_num = 0;
}
