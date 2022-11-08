/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:38:58 by akilk             #+#    #+#             */
/*   Updated: 2022/11/08 14:59:45 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
void	init_champion(t_champion *champion)
{
	t_champion	*new_champion;

	new_champion = (t_champion *)ft_memalloc(sizeof (t_champion));
	if (!new_champion)
		error(NULL, "Allocation failed in init_champion()");
}
*/
t_vm	*init_vm(void)
{
	t_vm	*vm;

	vm = (t_vm *)ft_memalloc(sizeof (t_vm));
	if (!vm)
		error(NULL, "Allocation failed in init_vm()");
	vm->champions_num = 0;
	return (vm);
}
